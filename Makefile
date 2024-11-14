sharedObject: headers/shared.h shared.c
	gcc -c shared.c

arcObject: headers/arc.h arc.c
	gcc -c arc.c

parserObject: headers/parser.h parser.c
	gcc -c parser.c

mainObject: main.c
	gcc -c main.c

all: shared.o parser.o arc.o main.o
	gcc shared.o arc.o parser.o main.o -o main.exe

clean:
	rm *.o main.exe