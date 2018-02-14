#include <unistd.h>
#include <stdio.h>

// Demoes the sbrk syscall
int main(int argc, char **argv) {
	while (1) {
		printf("sbrk=%lx\n", (unsigned long) sbrk(0));

		char c;
		int n = read(0, &c, 1);
		void *p = sbrk(4096);
		printf("  return %lx\n", (unsigned long) p);
	}
}
