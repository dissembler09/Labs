CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: myprogram
myprogram: main.o spacematrix.o
	$(CC) $(CFLAGS) -o myprogram main.o spacematrix.o
main.o: main.c spacematrix.h
	$(CC) $(CFLAGS) -c main.c
mystack.o: spacematrix.c spacematrix.h
	$(CC) $(CFLAGS) -c spacematrix.c
clean:
	rm -f myprogram *.o
