all: prog

src/funcoes.o: src/dados.h src/funcoes.c
	gcc -c src/funcoes.c -o src/funcoes.o

prog: main/main.c src/funcoes.o
	gcc main/main.c src/funcoes.o -o prog

run: prog
	prog.exe