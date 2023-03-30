all: main

main: baele.o alphalib.o
	gcc -o baele baele.o alphalib.o

alphalib.o: alphalib.h alphalib.c
	gcc -o alphalib.o alphalib.c -c

baele.o: baele.c
	gcc -o baele.o baele.c -c

clean:
	rm -rf *.o *~ main