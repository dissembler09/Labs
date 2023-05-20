CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: myprogram
myprogram: main.o mylist.o
	$(CC) $(CFLAGS) -o myprogram main.o mylist.o
main.o: main.c mylist.h
	$(CC) $(CFLAGS) -c main.c
mystack.o: mylist.c mylist.h
	$(CC) $(CFLAGS) -c mylist.c
clean:
	rm -f myprogram *.o
