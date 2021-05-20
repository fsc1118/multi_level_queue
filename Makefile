CC = gcc
CLAGS = -g -Wall -Werror -std=c11
all:queue.o mlq.o main.o
	$(CC) $(CLAGS) -o "multi level queue" queue.o mlq.o main.o
	rm *.o
queue.o:
	$(CC) $(CLAGS) -c queue.c
mlq.o:
	$(CC) $(CLAGS) -c mlq.c
main.o:
	$(CC) $(CLAGS) -c main.c
clean:
	rm *.exe