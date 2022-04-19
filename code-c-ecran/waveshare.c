#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "tty-UART1.h"

#define WS_RETURN_OK             0
#define WS_RETURN_ERR_GEN        -1

#define WS_X_RES                800
#define WS_Y_RES                600

#define WS_MAX_TEXT_FRAME       1020

#define WS_FRAME_HEADER         0xA5
#define WS_FRAME_FOOTER1        0xCC
#define WS_FRAME_FOOTER2        0x33
#define WS_FRAME_FOOTER3        0xC3
#define WS_FRAME_FOOTER4        0x3C

#define LENGTH_START 			0x00
#define LENGTH_END 				0x00

const char staticframe_handshake[] = {WS_FRAME_HEADER, 0x00, 0x09, 0x00, WS_FRAME_FOOTER1, WS_FRAME_FOOTER2, WS_FRAME_FOOTER3, WS_FRAME_FOOTER4, 0xAC};
const char staticframe_refresh[]   = {WS_FRAME_HEADER, 0x00, 0x09, 0x0A, WS_FRAME_FOOTER1, WS_FRAME_FOOTER2, WS_FRAME_FOOTER3, WS_FRAME_FOOTER4, 0xA6};
const char staticframe_clear[]     = {WS_FRAME_HEADER, 0x00, 0x09, 0x2E, WS_FRAME_FOOTER1, WS_FRAME_FOOTER2, WS_FRAME_FOOTER3, WS_FRAME_FOOTER4, 0x82};

const char staticframe_image[]     = {WS_FRAME_HEADER, 0x00, 0x16, 0x70, LENGTH_START, 0x00, 0x00, 0x00, 0x50, 0x49, 0x43, 0x31, 0x2E, 0x62, 0x6D, 0x70,LENGTH_END, WS_FRAME_FOOTER1, WS_FRAME_FOOTER2, WS_FRAME_FOOTER3, WS_FRAME_FOOTER4,  };


uint8_t XOR_checksum(char *frame, int length);

static int tty;

int wsInit(void)
{
        tty = tty_uart1_init();

        write(tty, staticframe_handshake, 9);

        char resp[2];
        read(tty, resp, 2);

        if (memcmp(resp, "OK", 2) == 0) {
                return WS_RETURN_OK;
        } else {
                return WS_RETURN_ERR_GEN;
        }
}

void wsClear(void)
{
        write(tty, staticframe_clear, 9);
}

void wsRefresh(void)
{
        write(tty, staticframe_refresh, 9);
}

void image_write(void)
{
		write(tty, staticframe_image, 22);
}

void wsDrawPoint(int x, int y)
{
        const int frameLength = 13;
        char frame[] = {WS_FRAME_HEADER, 0x00, frameLength, 0x20, 0x00, 0x00, 0x00, 0x00, WS_FRAME_FOOTER1, WS_FRAME_FOOTER2, WS_FRAME_FOOTER3, WS_FRAME_FOOTER4, 0x00};

        // Vérifier limites
        if ((x < 0) || (x > WS_X_RES) || (y < 0) || (y > WS_Y_RES)) {
                return;
        }

        // Obtenir les octets individuels de x et y et les placer dans la trame
        frame[4] = ((x >> 8) & 0xFF);
        frame[5] = (x & 0xFF);
        frame[6] = ((y >> 8) & 0xFF);
        frame[7] = (y & 0xFF);

        frame[12] = XOR_checksum(frame, frameLength);

        write(tty, frame, frameLength);
}

void wsDrawLine(int x1, int y1, int x2, int y2)
{
        const int frameLength = 17;
        char frame[] = {WS_FRAME_HEADER, 0x00, frameLength, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, WS_FRAME_FOOTER1, WS_FRAME_FOOTER2, WS_FRAME_FOOTER3, WS_FRAME_FOOTER4, 0x00};

        // Vérifier limites
        if ((x1 < 0) || (x1 > WS_X_RES) || (y1 < 0) || (y1 > WS_Y_RES) || (x2 < 0) || (x2 > WS_X_RES) || (y2 < 0) || (y2 > WS_Y_RES)) {
                return;
        }

        // Obtenir les octets individuels de x et y et les placer dans la trame
        frame[4] = ((x1 >> 8) & 0xFF);
        frame[5] = (x1 & 0xFF);
        frame[6] = ((y1 >> 8) & 0xFF);
        frame[7] = (y1 & 0xFF);
        frame[8] = ((x2 >> 8) & 0xFF);
        frame[9] = (x2 & 0xFF);
        frame[10] = ((y2 >> 8) & 0xFF);
        frame[11] = (y2 & 0xFF);

        frame[16] = XOR_checksum(frame, frameLength);

        write(tty, frame, frameLength);
}

void wsDisplayText(int posx, int posy, char text[], int length)
{
        // Vérifier limite de longueur
        if ((length < 0) || (length > WS_MAX_TEXT_FRAME)) {
                return;
        }
        // Vérifier limites de position
        if ((posx < 0) || (posx > WS_X_RES) || (posy < 0) || (posy > WS_Y_RES)) {
                return;
        }

        int frameLength = 13 + length;

        // Partie de la trame avant le texte, avec le header, la longueur, le byte de commande 0x30, et la position.
        char framePreText[] = {WS_FRAME_HEADER, 
                               ((frameLength >> 8) & 0xFF), (frameLength & 0xFF), 
                               0x30, 
                               ((posx >> 8) & 0xFF), (posx & 0xFF),
                               ((posy >> 8) & 0xFF), (posy & 0xFF)};
        // Partie de la trame après le texte, avec le footer et le checksum
        char framePostText[] = {WS_FRAME_FOOTER1, WS_FRAME_FOOTER2, WS_FRAME_FOOTER3, WS_FRAME_FOOTER4, 0x00};

        // Calcul du checksum en trois partie (pre, text et post)
        uint8_t checksum = XOR_checksum(framePreText, sizeof framePreText) ^ XOR_checksum(text, length) ^ XOR_checksum(framePostText, sizeof framePostText);
        framePostText[4] = checksum;

        write(tty, framePreText, sizeof framePreText);
        write(tty, text, length);
        write(tty, framePostText, sizeof framePostText);
}

uint8_t XOR_checksum(char *frame, int length)
{
        uint8_t xor = 0x00;

        for (int i = 0; i < length; i++) {
                xor ^= frame[i];
        }

        return xor;
}
 
