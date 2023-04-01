all: main

main: baele.o alphalib.o cypherlib.o
	gcc -o baele baele.o alphalib.o cypherlib.o

alphalib.o: alphalib.h alphalib.c
	gcc -o alphalib.o alphalib.c -c

cypherlib.o: cypherlib.h cypherlib.c
	gcc -o cypherlib.o cypherlib.c -c

baele.o: baele.c
	gcc -o baele.o baele.c -c

clean:
	rm -rf *.o *~ baele