CC=mpicc
CFLAGS=-I. -std=c99
DEPS = card.h hand.h deck.h
OBJ = card.o hand.o deck.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

monteCarloPoker: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm -f *.o *~ 
