#ifndef _COMMON_H
#define _COMMON_H

#include <netinet/in.h>

#define max(a, b) ((a >= b) ? a:b)

extern int errno;

typedef struct sockinfo {
	int fd;
	struct sockaddr_in *peer;
	int id;
	struct sockinfo *next;
	struct sockinfo *prev;
}_sockinfo, sockinfo;

int usage(char *instruction, char *argv[]);
sockinfo *sockinfo_init();
sockinfo *sockinfo_push(sockinfo *arr, sockinfo *target);
sockinfo *sockinfo_delete(sockinfo *arr, sockinfo *target);
int sockinfo_length(sockinfo *arr);

#endif // _COMMON_H
