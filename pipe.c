#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// Demoes using a pipe to communicate between parent and child process.
int main(int argc, char **argv) {
	int pipefd[2];
	if (pipe(pipefd) != 0) {
		printf("pipe() failed\n");
	}
	
	int pid = fork();
	if (pid == 0) {
		char buf[32];
		while (1) {
			int n = read(pipefd[0], buf, 32);
			write(1, buf, n);
		}
	} else {
		char *buf = "hello\n";
		while (1) {
			write(pipefd[1], buf, 6);
			sleep(1);
		}
	}
}
