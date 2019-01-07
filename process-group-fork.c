#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// This program demonstrates that the process group ID stays the same after a
// fork and is equal to the parent PID. The program also shows that the process
// group ID of the child stays the same even after the parent process exits.
//
// By extending the sleep period and simultaneously running ./forker it can be
// shown that the process group ID is not reused as a PID as long as at least
// one process exists in this process group.
void main(int argc, char **argv) {
	pid_t pid = fork();
	if (pid == 0) {
		printf(" [child]  PID: %d\n", getpid());
		printf(" [child] PGRP: %d\n", getpgrp());
		sleep(1);
		printf(" [child] PGRP: %d\n", getpgrp());
	} else {
		printf("[parent]  PID: %d\n", getpid());
		printf("[parent] PGRP: %d\n", getpgrp());
		exit(0);
	}
}
