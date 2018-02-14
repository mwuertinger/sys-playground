// 7.11 Exercise 2

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// Demoes opening the same file after a fork. The target file is written twice
// but truncated in between, thus leading to an exact copy of source. The
// offset within the file is not shared since each process opens it
// individually.
// Compare with 'The Design of the UNIX Operating System' chapter 7 exercise 2.
void main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: %s <source> <target>\n", argv[0]);
		exit(1);
	}

	int pid = fork();

	int fdrd = open(argv[1], O_RDONLY);
	if (fdrd == -1) {
		printf("[%d] failed to open %s\n", pid, argv[1]);
		exit(1);
	}
	int fdwt = creat(argv[2], 0666);
	if (fdwt == -1) {
		printf("[%d] failed to creat %s\n", pid, argv[2]);
		exit(1);
	}
	fdwt = open(argv[2], O_WRONLY);
	if (fdwt == -1) {
		printf("[%d] failed to open %s\n", pid, argv[2]);
		exit(1);
	}

	char c;
	for (;;) {
		if (read(fdrd, &c, 1) != 1) {
			return;
		}
		write(fdwt, &c, 1);
	}
}
