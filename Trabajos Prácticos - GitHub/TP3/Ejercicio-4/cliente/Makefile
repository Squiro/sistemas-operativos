CC = gcc
CFLAGS=-pthread -I.
OBJ=hacerConsultas.o cerrarSemaforo.o
BIN=hacerConsultas cerrarSemaforo

all: $(BIN)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): %: %.c
	$(CC) -o $@ $^ $(CFLAGS)