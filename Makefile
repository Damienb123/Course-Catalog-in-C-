CC=gcc
CFLAGS=-Wall -Wextra

assign4: assign.o
	$(CC) $(CFLAGS) -o assign4 assign4.o

assign4.o: assign4.c assign4.h
	$(CC) $(CFLAGS) -c assign4.c

clean:
	rm -f assign4.o assign4
