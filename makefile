build:

	gcc -Wall -o utils.o utils.c -c -g
	gcc -Wall -o utilizadores.o utilizadores.c -c -g
	gcc -Wall -o minHeap.o minHeap.c -c -g
	gcc -Wall -o localidade.o localidade.c -c -g
	gcc -Wall -o main.o main.c -c -g
	gcc -o main minHeap.o localidade.o utils.o utilizadores.o main.o

run:
	./main

clean:
	rm *.o
	rm main