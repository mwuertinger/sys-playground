#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

// Demoes reading every character as it comes from stdin without any buffering.
// Also disables input echoing to deliver unobstructed output.
void main(int argc, char **argv) {
	struct termios t;
	ioctl(0, TCGETS, &t);
	t.c_lflag &= ~(ICANON|ECHO);
	ioctl(0, TCSETSW, &t);

	char buf;
	while (read(0, &buf, 1) > 0) {
		printf("read: %c\n", buf);
	}
}
