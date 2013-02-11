#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include "../common/common.h"
#include "peer.h"
#include "listen.h"

#define N 4096

#define PEER_SUCCESS 0x00
#define PEER_DISCONNECTED 0x01
#define BROWSER_SUCCESS 0x02
#define BROWSER_DISCONNECTED 0x04


int process_read(sockinfo *ptr, int peer_fd, int listen_fd, sockinfo *sess);
int receive_from_peer(sockinfo *ptr);
sockinfo *accept_new_connection(sockinfo *listen, sockinfo *sessions);
int receive_from_browser(sockinfo *ptr, sockinfo *sess);

int fd_init(fd_set *fds, sockinfo *sess) {
	int maxfd = -1;
	sockinfo *ptr;

	FD_ZERO(fds);
	ptr = sess;
	for(ptr = sess; ptr != NULL; ptr = ptr->next) {
		FD_SET(ptr->fd, fds);
		maxfd = max(maxfd, ptr->fd);
	}
	return maxfd;
}

int main(int argc, char *argv[]) {
	int ret, state;
	int maxfd = -1;
	sockinfo *sess, *ptr, *peer, *listen;
	fd_set rfds;
	struct timeval tv;

	// arg checks
	if(argc != 3) {
		exit(usage("usage: %s remote_ip remote_port\n", argv));
	}

	// sess init
	sess = sockinfo_init();

	// establish connection with peer
	peer = connect_peer(argv[1], atoi(argv[2]));
	sess = sockinfo_push(sess, peer);
	// listen for connections from browser
	listen = proxy_listen(8080);
	sess = sockinfo_push(sess, listen);

	// main loop
	while(1) {
		printf("in the main loop\n");
		maxfd = fd_init(&rfds, sess);
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
		printf("current sockinfo_length: %d\n", sockinfo_length(sess));
		
		if (ret == -1)
			perror("select()");
		else if (ret == 0)
			printf("select() timed out\n");
		else {
			printf("selected\n");
			for(ptr = sess; ptr != NULL; ptr = ptr->next) {
				if(FD_ISSET(ptr->fd, &rfds)) {
					state = process_read(ptr, peer->fd, listen->fd, sess);
				}
			}
		}
		if (state == PEER_DISCONNECTED)
			break;
	}

	// 終了処理
	for(ptr = sess; ptr != NULL && ptr->next != NULL; ptr = ptr->next) {
		close(ptr->fd);
	}
	exit(0);
}

int process_read(sockinfo *ptr, int peer_fd, int listen_fd, sockinfo *sess) {
	if (ptr->fd == peer_fd) {
		return receive_from_peer(ptr);
	}else if(ptr->fd == listen_fd) {
		sess = accept_new_connection(ptr, sess);
	}else{
		return receive_from_browser(ptr, sess);
	}
	return 0;
}

int receive_from_peer(sockinfo *ptr) {
	char data[4096];
	int recvbytes = recv(ptr->fd, data, N, 0);
	if (recvbytes <= 0) {
		return PEER_DISCONNECTED;
	}
	printf("received: %s\n", data);
	return PEER_SUCCESS;
}

sockinfo *accept_new_connection(sockinfo *listen, sockinfo *sessions) {
	socklen_t l;
	sockinfo *newsess = (sockinfo *)malloc(sizeof(sockinfo));
	sessions = sockinfo_push(sessions, newsess);
	newsess->peer = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	l = sizeof(struct sockaddr_in);
	newsess->fd = accept(listen->fd, (struct sockaddr *)newsess->peer, &l);
	printf("Connection established: %s:%u\n", inet_ntoa(newsess->peer->sin_addr), ntohs(newsess->peer->sin_port));
	return sessions;
}

int receive_from_browser(sockinfo *ptr, sockinfo *sess) {
	char data[4096];
	int recvbytes = recv(ptr->fd, data, N, 0);
	if (recvbytes <= 0) {
		close(ptr->fd);
		sess = sockinfo_delete(sess, ptr);
		return BROWSER_DISCONNECTED;
	}
	//printf("received: %s\n", data);
	write(sess->fd, data, recvbytes);
	return BROWSER_SUCCESS;
}
