CC = gcc
CFLAGS=-pthread -I.
OBJ=cliente.o 
BIN=cliente 

all: $(BIN)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): %: %.c
	$(CC) -o $@ $^ $(CFLAGS)