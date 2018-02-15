#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

// This demo creates a new pseudoterminal and then execs and attaches whatever
// command is specified in argv to it. The commands output is dumped to the
// screen either as-is or as hex for non-printable characters.
//
// Thepurpose of this program is to better understand how applications interact
// with a terminal device.
//
// Example: ./terminal `which top`
int main(int argc, char **argv) {
	// Disable buffering for stdout
	setvbuf(stdout, 0, _IONBF, 0);

	int masterFd = open("/dev/ptmx", O_RDWR);
	if (masterFd < 0) {
		printf("opening /dev/ptmx failed: %d\n", errno);
		return 1;
	}

	int zero = 0;
	int error = ioctl(masterFd, TIOCSPTLCK, &zero);
	if (error != 0) {
		printf("ioctl TIOCSPTLCK failed: %d\n", errno);
		return 1;
	}

	int slave;
	error = ioctl(masterFd, TIOCGPTN, &slave);
	if (error != 0) {
		printf("ioctl TIOCGPTN failed: %d\n", errno);
		return 1;
	}

	char slavePath[16];
	snprintf(slavePath, 16, "/dev/pts/%d", slave);
	int slaveFd = open(slavePath, O_RDWR, O_NOCTTY);
	if (slaveFd < 0) {
		printf("opening %s failed: %d\n", slavePath, errno);
		return 1;
	}

	struct winsize ws;
	ws.ws_row = 30;
	ws.ws_col = 80;
	error = ioctl(masterFd, TIOCSWINSZ, &ws);
	if (error != 0) {
		printf("setting window size failed: %d\n", errno);
		return 1;
	}

	int pid = fork();
	if (pid == 0) {
		close(0);
		close(1);
		close(2);
		dup(slaveFd);
		dup(slaveFd);
		dup(slaveFd);

		for (int i = 1; i < argc; i++) {
			argv[i - 1] = argv[i];
		}
		argv[argc - 1] = 0;

		char *envp[] = {"TERM=xterm-256color", 0};

		execve(argv[0], argv, envp);
		printf("execve failed: %d\n", errno);
		return 1;
	} else {
		while (1) {
			char buf;
			if (read(masterFd, &buf, 1) < 0) {
				printf("read from masterFd failed: %d\n", errno);
				return 1;
			}
			if (buf == EOF) {
				break;
			}

			if (isprint(buf) || buf == '\n' || buf == '\r' || buf == 0x0b) {
				printf(" %c", buf);
			} else {
				printf("%02x", buf);
			}

//			if (write(1, &buf, 1) < 1) {
//				printf("write to stdout failed: %d\n", errno);
//				return 1;
//			}
		}
		wait(0);
	}
}
