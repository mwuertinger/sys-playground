#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>

// child thread entry point
int child(void *args) {
	printf("child: pid=%d, tid=%ld\n", getpid(), syscall(SYS_gettid));
	sleep(3600);
}

int main(int argc, char **argv) {
	printf("parent: pid=%d, tid=%ld\n", getpid(), syscall(SYS_gettid));

	// allocate stack memory
	int stack_size = 4096;
	void *child_stack = mmap(NULL, stack_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0) + stack_size;
	if (child_stack == (void*) -1) {
		perror("mmap");
		return 1;
	}

	// create a new thread
	int tid = clone(child, child_stack, CLONE_THREAD|CLONE_SIGHAND|CLONE_VM, NULL);
	if (tid == -1) {
		perror("clone");
		return 2;
	}

	sleep(3600);
}
