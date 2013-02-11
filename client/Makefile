CFLAGS = -Wall -g
TARGET = nsa-client
TARGETS = $(TARGET)
COMMON = $(shell ls ../common/*.c)
SRCS = $(shell ls *.c) $(COMMON)
OBJS = $(SRCS:.c=.o)

include ../Makefile.in

all: $(TARGETS) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
