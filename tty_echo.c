#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

// Demoes disabling terminal echo functionality
void main(int argc, char **argv) {
	struct termios t;
	ioctl(0, TCGETS, &t);
	t.c_lflag &= ~ECHO;
	ioctl(0, TCSETSW, &t);
}
