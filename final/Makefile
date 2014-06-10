CC=mpicc
CFLAGS=-I. -std=c99
DEPS = card.h hand.h deck.h
OBJ = card.o hand.o deck.o
MAINS = mainBasic.o mainDerived.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

basic: $(OBJ) mainBasic.o
	$(CC) -o pokerBasic $^ $(CFLAGS)

derived: $(OBJ) mainDerived.o
	$(CC) -o pokerDerived $^ $(CFLAGS)

clean:
	rm -f *.o *~ 
