/*
 * POSIX
 * シリアルポートのDTRピンを指定した回数LOWにする
*/


#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MILLISEC 1000000

void usage(char app[]) {
	printf("USAGE: %s [PORT] [WAIT] [COUNT]\n",app);
}


int main(int argc, char *argv[]) {
	if(argc <= 3) {
		usage(argv[0]);
	}

	int fd = open(argv[1],O_RDWR | O_NOCTTY );
	struct timespec wait = {0, strtol(argv[2],NULL,10) * MILLISEC};
	int modem = 0;

	for(int i=0; i < strtol(argv[3],NULL,10); i++) {
		ioctl(fd, TIOCMGET, &modem);

		modem |= TIOCM_DTR;
		ioctl(fd, TIOCMSET, &modem);

		nanosleep(&wait,NULL);

		modem &= ~TIOCM_DTR;
		ioctl(fd, TIOCMSET, &modem);

		nanosleep(&wait,NULL);
	}

	close(fd);
}
