#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// Demoes the use of effective and real user IDs.
// The demo assumes that the executable has the setuid bit set, is owned by the
// user specified in 'owner' and is executed by the user specified in 'caller'.
int main(int argc, char **argv) {
	int owner = 1000;
	int caller = 1010;

	printf("uid=%d euid=%d\n", getuid(), geteuid());

	printf("setuid(%d)\n", caller);
	setuid(caller);

	printf("uid=%d euid=%d\n", getuid(), geteuid());

	printf("setuid(%d)\n", owner);
	setuid(owner);

	printf("uid=%d euid=%d\n", getuid(), geteuid());

	return 0;
}
