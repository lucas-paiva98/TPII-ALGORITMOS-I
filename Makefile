CC := gcc

all: tp2.out

tp2.out: utils.o distance.o
	$(CC) utils.o distance.o tp2.c -o tp2.out -lm

utils.o: utils.c
	$(CC) -c utils.c -o utils.o

distance.o: distance.c
	$(CC) -c distance.c -o distance.o

clean:
	rm -f tp2 utils.o distance.o

run:
	./tp2.out $(BLA)