#include "../common/common.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

sockinfo *proxy_listen(int listen_port) {
	sockinfo *srv;
	int ret;
	
	srv = (sockinfo *)malloc(sizeof(sockinfo));
	srv->peer = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

	srv->fd = socket(PF_INET, SOCK_STREAM, 0);
	assert(srv->fd != -1);
	srv->peer->sin_family = AF_INET;
	srv->peer->sin_addr.s_addr = INADDR_ANY;
	srv->peer->sin_port = htons(8080);
	ret = bind(srv->fd, (struct sockaddr *)srv->peer, sizeof(struct sockaddr_in));
	if(ret != 0) {
		printf("errno: %d\n", errno);
		perror("bind()");
		exit(0);
	}
	assert(listen(srv->fd, 256) == 0);
	return srv;
}
