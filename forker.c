#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// This program calls fork() as quickly as possible to change its PID and to
// disguise its existence. It is very hard to spot such a program in usual tools
// like `ps`.
// The program prints its process group ID in the beginning. The process can be
// killed by executing `kill -9 -$PGPID`.
//
// Not that unlike a fork-bomb this program does not aim to exhaust system
// resouces by spawning as many processes as possible. It is therefore safe to
// run.
int main(int argc, char **argv) {
        printf("PGRP: %d\n", getpgrp());
        printf("You can kill this process with the following command: ");
	printf("kill -9 -%d\n", getpgrp());
        sleep(10);
        while (fork() < 1) {
                printf("%d\n", getpid());
        }
}
