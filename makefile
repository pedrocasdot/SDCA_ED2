build:

	gcc  -o utils.o utils.c -c 
	gcc  -o utilizadores.o utilizadores.c -c 
	gcc  -o minHeap.o minHeap.c -c 
	gcc  -o localidade.o localidade.c -c 
	gcc  -o main.o main.c -c 
	gcc -o main *.o 

run:
	./main

clean:
	rm *.o
	rm main