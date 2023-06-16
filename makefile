build:
	gcc -Wall -o utils.o utils.c -c
	gcc -Wall -o utilizadores.o utilizadores.c -c
	gcc -Wall -o main.o main.c -c
	gcc -o main utils.o utilizadores.o main.o

run:
	./main

clean:
	rm *.o
	rm main