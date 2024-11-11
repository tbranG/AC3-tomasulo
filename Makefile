parserObject: headers/shared.h headers/parser.h parser.c
	gcc -c parser.c

mainObject: headers/parser.h main.c
	gcc -c main.c

all: parser.o main.o
	gcc parser.o main.o -o main.exe

clean:
	rm *.o main