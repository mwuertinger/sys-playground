#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// Demoes file descriptor handling after a fork. Note that the processes read
// different portions of the file since they share the file offset.
int main(int argc, char **argv) {
	int fd = open("/etc/passwd", O_RDONLY);
	int pid = fork();
	printf("[%d] fd=%d\n", pid, fd);
	
	char buf[16];
	// wait for user
	read(0, buf, 1);

	int n = read(fd, buf, 15);
	buf[15] = 0;
	printf("[%d] read %d bytes: %s\n", pid, n, buf);
	
	// wait for user
	read(0, buf, 1);

	if (pid == 0) {
		wait(0);
	}
}
