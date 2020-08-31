all: servidor cliente

servidor: servidor.o
	g++ -o servidor servidor.o 
servidor.o: servidor.c
	g++ -c servidor.c

cliente: cliente.o
	g++ -o cliente cliente.o 

cliente.o: cliente.c
	g++ -c cliente.c


clean: 
	rm *.o 




