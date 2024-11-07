CC=gcc
CFLAGS=-I. -w -g
DEPS = main.h
OBJ = main.o hello.o bye.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

greetings: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)