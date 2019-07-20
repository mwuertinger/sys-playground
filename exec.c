#include <stdio.h>
#include <unistd.h>

// demonstrates how the virtual address space changes after a call to execve thanks to ASLR
int main(int argc, char **argv) {
	printf("pid=%d, break=%p\n", getpid(), sbrk(0));
	execve(argv[0], argv, NULL);
	perror("execve");
	return 1;
}
