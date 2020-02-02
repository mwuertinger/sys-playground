#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// Create an unnamed temporary file and write some data into it.
int main(int argc, char **argv) {
	int fd = open("/tmp", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		perror(NULL);
		exit(1);
	}
	while (1) {
		char buf[1024];
		ssize_t res = write(fd, buf, 1024);
		if (res < 0) {
			perror(NULL);
			exit(1);
		}
		sleep(1);
	}
	return 0;
}
