#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <assert.h>
#include "../common/common.h"
#include "peer.h"

sockinfo *connect_peer(char *srv_addr, int srv_port) {
	sockinfo *info;

	// establish contenious session
	info = (sockinfo *)malloc(sizeof(sockinfo));
	info->fd = socket(PF_INET, SOCK_STREAM, 0);
	info->peer = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	info->peer->sin_family = AF_INET;
	info->peer->sin_addr.s_addr = inet_addr(srv_addr);
	info->peer->sin_port = htons(srv_port);
	assert(connect(info->fd, (struct sockaddr *)info->peer, sizeof(struct sockaddr_in)) != -1);

	fprintf(stderr, "connected to %s:%u", srv_addr, srv_port);
	return info;
}
