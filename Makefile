CC = gcc
CGLAGS = -Wall -O2

TABLE_SIZE ?= 1024
CFLAGS += -DTABLE_SIZE=$(TABLE_SIZE)

all: main

main: map.c
	$(CC) $(CGLAGS) map.c -o map

clean:
	rm -rf map
