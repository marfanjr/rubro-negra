all: ArvRN clean

ArvRN: ArvRN.o libArvRN.o
	gcc ArvRN.o libArvRN.o -o ArvRN

ArvRN.o: ArvRN.c libArvRN.h
	gcc -c ArvRN.c -o ArvRN.o

libArvRN.o: libArvRN.c libArvRN.h
	gcc -c libArvRN.c -o libArvRN.o

clean:
	rm -rf *.o
