CC = gcc
CFLAGS=-I.
OBJ=hacerConsultas.o leerResultado.o
BIN=hacerConsultas leerResultado

all: $(BIN)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): %: %.c
	$(CC) -o $@ $^ $(CFLAGS)