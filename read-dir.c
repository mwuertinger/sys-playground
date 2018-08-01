#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Demonstrates that reading from a file descriptor representing a directory
// fails with an error.
int main(int argc, char **argv) {
	int fd = open("/", O_RDONLY);
	char buf[16];
	int n = read(fd, buf, 15);
	if (n < 0) {
		perror(NULL);
	} else {
		buf[n] = 0;
		printf("read %d bytes: %s\n", n, buf);
	}
}
