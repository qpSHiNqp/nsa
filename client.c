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

int usage(int argc, char *argv[]) {
	printf("usage: %s remote_ip port\n", argv[0]);
	return 0;
}

int main(int argc, char *argv[]) {
	int s, ret, n;
	struct sockaddr_in addr;
	const char *data = "test message\n";

	// arg checks
	if(argc != 3) {
		exit(usage(argc, argv));
	}

	s = socket(PF_INET, SOCK_STREAM, 0);
	assert(s != -1);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
	assert(ret != -1);

	send(s, data, strlen(data), MSG_OOB);

	close(s);
	exit(0);
}
