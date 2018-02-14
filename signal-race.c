#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handler() {
	printf("PID %d caught one\n", getpid());
	sleep(1);
	signal(SIGINT, handler);
}

// Tries to reproduce the behavior described in 'The Design of the UNIX
// Operating System' Figure 7.12. According to the book the parent process gets
// killed if it gets preempted in the signal handler before calling 'signal'
// again since the disposition of the signal is reset to SIG_DFL once the
// handler is invoked.
// However, this behavior cannot be reproduced on Linux 4.13. According to
// SIGNAL(2) the use of this function is discouraged due to portability issues
// and sigaction should be used instead.
void main(int argc, char **argv) {
	signal(SIGINT, handler);

	if (fork() == 0) {
		sleep(5);
		int ppid = getppid();
		for (;;) {
			if (kill(ppid, SIGINT) == -1) {
				exit(0);
			}
		}
	}

	nice(19);
	for (;;) {}
}
