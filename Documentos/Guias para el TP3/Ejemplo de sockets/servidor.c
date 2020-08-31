#include <netdb.h>		
#include <stdio.h>	
#include <string.h>		
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_QUEUE 5
#define WORDS 3

int main(int argc, char *argv[])
{
	socklen_t cl=sizeof(struct sockaddr_in);
	struct sockaddr_in sa;
	struct sockaddr_in ca;
 	int server_socket;
	int client_socket;
	int habilitar = 1;
	int pts=0;	
	char 	buffer[256];
	char	words[][10]={"casa","perro","auto"};
		
	//Espera al menos un parámetro: Puerto de escucha
	//argc se establece en 1 si no se ingresan parámetros
	if( argc < 2 ){
		printf("Debe ingresar el puerto de escucha !!!\n");	
		return 1;	
	}
		
	//Crear el socket de escucha del servidor
	if((server_socket=socket(AF_INET,SOCK_STREAM,0)) ==-1){
		printf("No se pudo crear el socket !!!\n");	
		return 1;
	}

	//Configurar opciones del socket
	//En este caso que se pueda reutilizar la dirección y puerto 	
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &habilitar, sizeof(int)) < 0){
   	printf("No se pudo configurar opciones del socket !!!\n");	
		return 1;
	}
	
	//Configuración del servidor
	bzero((char *) &sa, sizeof(struct sockaddr_in));
 	sa.sin_family 		= AF_INET;
 	sa.sin_port 		= htons(atoi(argv[1]));
	sa.sin_addr.s_addr= INADDR_ANY;
 	
	//Vincular socket con configuracion del servidor
	bind(server_socket,(struct sockaddr *)&sa,sizeof(struct sockaddr_in));    
	
	//Marcar el socket como "Socket Pasivo" y Establecer la máxima 
	//cantidad de peticiones que pueden ser encoladas
	listen(server_socket,MAX_QUEUE);
	
	
	//El servidor ser bloquea a la espera de una peticion de conexión
	//desde el cliente (connect) 
 	client_socket=accept(server_socket,(struct sockaddr *) &ca,&cl);
	
	for(int i=0;i<WORDS;i++)
 	{  		
		bzero(buffer,256);
		send(client_socket,words[i],strlen(words[i]),0);
		printf("%s\n",words[i]);
		recv(client_socket,buffer,256,0);
		printf("%s\n",buffer);
 		if (!strcmp(buffer,words[i]))
		{
			send(client_socket,"CORRECTO +10 pts\n",17,0);
			pts+=10;		
		}		
		else
			send(client_socket,"INCORRECTO +0 pts\n",18,0);
	}

	sprintf(buffer,"SU PUNTAJE ES: %d\n", pts);
	send(client_socket, buffer, strlen(buffer), 0);
	
 	close(client_socket);
 	close(server_socket);
 	return 0; 
};















