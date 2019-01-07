#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// This program can demonstrate how the shell handles process groups:
// $ ./process-group | ./process-group 
//           PID: 4934
// process group: 4933
//           PID: 4933
// process group: 4933
//
// As you can see a shell pipeline is a single process group. The process group
// ID matches one of the two process IDs. This process is the group leader.
void main(int argc, char **argv) {
	fprintf(stderr, "          PID: %d\n", getpid());
	fprintf(stderr, "process group: %d\n", getpgrp());
}
