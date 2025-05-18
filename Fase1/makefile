all: prog

funcoes.o: dados.h funcoes.c
	gcc -c funcoes.c -o funcoes.o

prog: main.c funcoes.o
	gcc main.c funcoes.o -o prog

run: prog
	prog.exe

clean:
	rm -f *.o prog TA
