#include <unistd.h>
#include <stdio.h>

// Demoes that disabling buffernig for stdin does not help revealing input
// before a line break. The reason for that is that the terminal does not write
// the input to the tty before the user hits enter.
void main() {

	// Disabling buffering for stdin does not make a difference.
	setvbuf(stdin, NULL, _IONBF, 0);

	char buf;
	int n = read(0, &buf, 1);

	printf("read %d bytes: %c\n", n, buf);
}
