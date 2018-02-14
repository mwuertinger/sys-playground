#include <unistd.h>
#include <stdio.h>

// Run this demo once on a terminal and once redirecting stdout to a file. You
// will observe that in the second case the word 'hello' appears twice. The
// reason for this surprising behavior is that terminals use line buffering by
// default which flushes 'hello' since it's followed by a '\n'. When writing to
// a file output is fully buffered by default, meaning that the output is cached
// until it hits a certain threshold or the program terminates. At the fork()
// the buffer (containing 'hello') is cloned and then flushed in both processes.
//
// Compare to SETBUF(3): 'Normally all files are block buffered.  If a stream
// refers to a terminal (as stdout normally does), it is line buffered.'
//
// See also: 'The Design of the UNIX Operating System' chapter 7 exercise 1.
void main() {

	// Default buffering behavior can be modified:
	// Enforce line buffering:
	// setvbuf(stdout, NULL, _IOLBF, 0);
	// Enforce block buffering:
	// setvbuf(stdout, NULL, _IOFBF, 1024);

	printf("hello\n");
	if (fork() == 0) {
		printf("world\n");
	}
}
