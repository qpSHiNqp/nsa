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
	printf("usage: %s remote_ip port\n", argv[0]);
	return 0;
}

int main(int argc, char *argv[]) {
	int s, ret, n;
	int sp_sock, cp_sock;
	struct sockaddr_in addr;
	struct sockaddr_in s_proxy;
	struct sockaddr_in c_proxy;
	char data[1024] = "test message\n";

	// arg checks
	if(argc != 3) {
		exit(usage(argc, argv));
	}

	// establish contenious session
	s = socket(PF_INET, SOCK_STREAM, 0);
	assert(s != -1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
	if(ret != 0) {
		printf("errno: %d\n", errno);
		exit(0);
	}

	// listen for connections from browser
	sp_sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sp_sock != -1);

	s_proxy.sin_family = AF_INET;
	s_proxy.sin_addr.s_addr = INADDR_ANY;
	s_proxy.sin_port = htons(8080);

	ret = bind(sp_sock, (struct sockaddr *)&s_proxy, sizeof(s_proxy));
	if(ret != 0) {
		printf("errno: %d\n", errno);
		exit(0);
	}

	assert(listen(s_proxy, 5) == 0);
	while(1) {
		char data[1024];

		printf("server waiting\n");

		c_proxy = accept(s_proxy, (struct sockaddr *)&c_proxy, &c_addr_len);

		recv(c_sock, data, sizeof(data), 0);
		sprintf(buf, "you sent: %s\n", data);
		send(c_sock, buf, strlen(buf), 0);
		close(c_sock);
	}
	close(s_sock);
	exit(0);
	send(s, data, strlen(data), 0);
	recv(s, (void *)data, sizeof(data), 0);
	printf(">%s\n", data);

	close(s);
	exit(0);
}
