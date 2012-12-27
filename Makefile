# Makefile for nsa
# created on 2012/12/23
# by tanaka@hongo.wide.ad.jp

CLIENT = nsa-client
SERVER = nsa-server
TARGET = $(CLIENT) $(SERVER)
CXXFLAGS += -O3 -Wall
LDFLAGS += -lc
OBJS_CLI = client.o
OBJS_SRV = server.o

all: $(TARGET)

$(CLIENT): $(OBJS_CLI)
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CLI)

$(SERVER): $(OBJS_SRV)
	$(CC) -o $@ $(LDFLAGS) $(OBJS_SRV)

clean:
	$(RM) $(OBJS)

