all: serialize
	gcc main.o -o serialize
serialize: main.c
	gcc -c main.c -o main.o



