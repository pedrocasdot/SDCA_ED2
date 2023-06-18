build:

	gcc -Wall -o utils.o utils.c -c
	gcc -Wall -o utilizadores.o utilizadores.c -c
	gcc -Wall -o localidade.o localidade.c -c
	gcc -Wall -o minHeap.o minHeap.c -c
	gcc -Wall -o main.o main.c -c
	gcc -o main minHeap.o localidade.o utils.o utilizadores.o main.o

run:
	./main

clean:
	rm *.o
	rm main