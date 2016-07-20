CFLAGS += -Wall -g

# make has a builtin rule to create .o files out of .c files

all:	array tree make-random-ints

array:	main.o array.o
	gcc -o $@ $^ $(LDFLAGS)
tree:	main.o tree.o
	gcc -o $@ $^ $(LDFLAGS)

make-random-ints:	make-random-ints.o
	gcc -o $@ $^ $(LDFLAGS)

