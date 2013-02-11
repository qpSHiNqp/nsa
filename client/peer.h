#ifndef _PEER_H
#define _PEER_H

#include <sys/socket.h>
#include "../common/common.h"

sockinfo *connect_peer(char *srv_addr, int srv_port);

#endif // _PEER_H
