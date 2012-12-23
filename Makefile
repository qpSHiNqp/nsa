# Makefile for nsa
# created on 2012/12/23
# by tanaka@hongo.wide.ad.jp

TARGET = nsa-client
CXXFLAGS += -O3 -Wall
LDFLAGS += -lc
OBJS = client.o

all: $(TARGET)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJS)

$(TARGET): $(OBJS)

clean:
	$(RM) $(OBJS)

