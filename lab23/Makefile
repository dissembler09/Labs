CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: myprogram
myprogram: tree.o mytree.o
	$(CC) $(CFLAGS) -o myprogram tree.o mytree.o
main.o: tree.c mytree.h
	$(CC) $(CFLAGS) -c tree.c
mystack.o: mytree.c mytree.h
	$(CC) $(CFLAGS) -c mytree.c
clean:
	rm -f myprogram *.o
