CC=gcc


all: tp2
tp2: distance.o
distance.o: tp2.c distance.h distance.h

clean:
		rm -f tp2 distance.o
run: tp2
		./tp2
