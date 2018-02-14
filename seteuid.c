#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// Demoes setting different values for the effective user id.
// Try running as different users (including root) and with the setuid bit set.
int main(int argc, char **argv) {
	int euid = 1010;

	printf("uid=%d euid=%d\n", getuid(), geteuid());

	printf("seteuid(%d)\n", euid);
	seteuid(euid);

	printf("uid=%d euid=%d\n", getuid(), geteuid());

	printf("seteuid(%d)\n", 0);
	seteuid(0);

	printf("uid=%d euid=%d\n", getuid(), geteuid());

	return 0;
}
