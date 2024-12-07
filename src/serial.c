#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "serial.h"

// STILL INCOMPLETE.
// https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c


static const char* portname = "/dev/ttyS0";

int set_interface_attribs(int fd, int baud, int parity)
{
	struct termios tty;
	if (tcgetattr(fd, &tty) != 0)
	{
		perror("tcgetattr");
		return -1;
	}

	cfsetospeed(&tty, baud);
	cfsetispeed(&tty, baud);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
	tty.c_iflag &= ~IGNBRK; // disable break processing
	tty.c_lflag = 0; // no signaling chars, no echo, no canonical processing
	tty.c_oflag = 0; // no remapping, no delays
	tty.c_cc[VMIN]  = 0; // read does not block
	tty.c_cc[VTIME] = 5; // 0.5 second read timeout
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // disable xon/xoff ctrl
	tty.c_cflag |= (CLOCAL | CREAD); // ignore modem controls, enable reading
	tty.c_cflag &= ~(PARENB | PARODD); // noshut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		perror("tcsetattr");
		return -1;
	}
	
	return 0;
}
