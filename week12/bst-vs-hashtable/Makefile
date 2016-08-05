CFLAGS += -Wall -g
LDFLAGS += -lm

all:	tree hash-table

tree:	main.o tree.o
	$(CC) -o $@ $^ $(LDFLAGS)
hash-table:	main.o hash-table.o
	$(CC) -o $@ $^ $(LDFLAGS)
