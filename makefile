build:

	gcc  -o utils.o utils.c -c -g -lcrypto
	gcc  -o utilizadores.o utilizadores.c -c -g -lcrypto
	gcc  -o minHeap.o minHeap.c -c -g -lcrypto
	gcc  -o localidade.o localidade.c -c -g -lcrypto
	gcc  -o main.o main.c -c -g -lcrypto
	gcc -o main minHeap.o localidade.o utils.o utilizadores.o main.o -lcrypto

run:
	./main

clean:
	rm *.o
	rm main