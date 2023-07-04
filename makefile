build:

	gcc  -o utils.o utils.c -c -g
	gcc  -o utilizadores.o utilizadores.c -c -g
	gcc  -o minHeap.o minHeap.c -c -g
	gcc  -o localidade.o localidade.c -c -g
	gcc -o menu.o menu.c -c -g
	gcc  -o main.o main.c -c  -g
	gcc -o main *.o 

run:
	./main

clean:
	rm *.o
	rm main