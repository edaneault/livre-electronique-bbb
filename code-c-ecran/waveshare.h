#ifndef WAVESHARE_H
#define WAVESHARE_H

int wsInit(void);
void wsClear(void);
void wsRefresh(void);
void image_write(void);
void wsDrawPoint(int x, int y);
void wsDrawLine(int x1, int y1, int x2, int y2);
void wsDisplayText(int posx, int posy, char text[], int length);
void lookatmicrosd(void);

#endif
