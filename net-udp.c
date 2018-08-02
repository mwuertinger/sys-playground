#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int port = atoi(argv[1]);
	struct sockaddr_in listenaddr;
	memset(&listenaddr, 0, sizeof(struct sockaddr_in));
	listenaddr.sin_family = AF_INET;
	listenaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	listenaddr.sin_port = htons((unsigned short)port);

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		fprintf(stderr, "unable to create socket\n");
		return 1;
	}
	if (bind(sock, (struct sockaddr *)&listenaddr, sizeof(listenaddr)) != 0) {
		fprintf(stderr, "unable to bind socket\n");
		perror(NULL);
		return 1;
	}

	int BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len = sizeof(struct sockaddr_storage);
	for (;;) {
		int n = recvfrom(sock, buf, BUF_SIZE - 1, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);
		if (n < 0) {
			perror(NULL);
			continue;
		}
		buf[n] = '\0'; // terminate string

		char host[NI_MAXHOST];
		char service[NI_MAXSERV];

		int err = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
		if (err != 0) {
			fprintf(stderr, "getnameinfo failed\n");
			perror(NULL);
			continue;
		}
		printf("%s:%s: received %d bytes: %s\n", host, service, n, buf);
	}
}
