CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: myprogram
myprogram: main.o mytree.o
	$(CC) $(CFLAGS) -o myprogram main.o mytree.o
main.o: main.c mytree.h
	$(CC) $(CFLAGS) -c main.c
mystack.o: mytree.c mytree.h
	$(CC) $(CFLAGS) -c mytree.c
clean:
	rm -f myprogram *.o
