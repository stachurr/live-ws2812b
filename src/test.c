#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include <signal.h>

static const char* portname = "/dev/ttyS0";
static int g_signal = 0;

void signal_handler(int signum)
{
	g_signal = signum;
}


int main(void)
{
	int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}

	printf("%s opened on fd %d\n", portname, fd);

	while (g_signal == 0)
		;

	close(fd);	
	return 0;
}

