#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <assert.h>

extern int errno;

int usage(int argc, char *argv[]) {
	  printf("usage: %s port\n", argv[0]);
		return 0;
}

int main(int argc, char *argv[]) {
	int s_sock, c_sock, ret, n;
	socklen_t c_addr_len;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	char data[1024];
	char buf[1024];

	// arg checks
	if(argc != 2) {
		exit(usage(argc, argv));
	}

	s_sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(s_sock != -1);

	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = INADDR_ANY;
	s_addr.sin_port = htons(atoi(argv[1]));

	ret = bind(s_sock, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret != 0) {
		printf("errno: %d\n", errno);
		exit(0);
	}

	assert(listen(s_sock, 5) == 0);
	while(1) {
		char data[1024];

		printf("server waiting\n");

		c_sock = accept(s_sock, (struct sockaddr *)&c_addr, &c_addr_len);

		recv(c_sock, data, sizeof(data), 0);
		sprintf(buf, "you sent: %s\n", data);
		send(c_sock, buf, strlen(buf), 0);
		close(c_sock);
	}
	close(s_sock);
	exit(0);
}

