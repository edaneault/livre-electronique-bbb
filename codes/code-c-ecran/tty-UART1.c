#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define TTY_UART1_RETURN_OK             0
#define TTY_UART1_RETURN_ERR_GEN        -1

#define TTY_UART1_SPEED                 B115200
#define TTY_UART1_PATH                  "/dev/ttyO1"

/* 
 * Pour utiliser après initialisation :
 * write (fd, "hello!\n", 7);           // send 7 character greeting
 *
 * usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
 *                                      // receive 25:  approx 100 uS per char transmit
 * char buf [100];
 * int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
 */

static int fd;

int tty_uart1_init(void)
{
        fd = open(TTY_UART1_PATH, O_RDWR | O_NOCTTY | O_SYNC);

        if (fd < 0)
        {
                return TTY_UART1_RETURN_ERR_GEN;
        }

        struct termios tty;
        if (tcgetattr (fd, &tty) != 0)
        {
                return TTY_UART1_RETURN_ERR_GEN;
        }

        cfsetospeed (&tty, TTY_UART1_SPEED);
        cfsetispeed (&tty, TTY_UART1_SPEED);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                return TTY_UART1_RETURN_ERR_GEN;
        }

        return fd;
}
