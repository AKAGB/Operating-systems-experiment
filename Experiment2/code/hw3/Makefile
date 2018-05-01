prog: main.o apue.o
	gcc -o prog main.o apue.o

main.o: main.c apue.h
	gcc -Wall -g -c main.c

apue.o: apue.c
	gcc -Wall -c apue.c

clean:
	rm *.o