CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: myprogram
myprogram: main.o mystack.o
	$(CC) $(CFLAGS) -o myprogram main.o mystack.o
main.o: main.c mystack.h
	$(CC) $(CFLAGS) -c main.c
mystack.o: mystack.c mystack.h
	$(CC) $(CFLAGS) -c mystack.c
clean:
	rm -f myprogram *.o
