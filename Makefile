sharedObject: headers/shared.h shared.c
	gcc -c shared.c

arcObject: headers/arc.h arc.c
	gcc -c arc.c

parserObject: headers/parser.h parser.c
	gcc -c parser.c

utilsObject: headers/utils.h utils.c
	gcc -c utils.c

mainObject: main.c
	gcc -c main.c

all: shared.o parser.o arc.o utils.o main.o
	gcc shared.o arc.o parser.o utils.o main.o -o main.exe

clean:
	rm *.o main.exe