#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>	

int main(int argc, char *argv[])
{	
	int x;
	char buffer[256];
	struct sockaddr_in sa; //Configuración del servidor
	
	//Espera al menos dos parámetros: IP y Puerto de escucha
	if( argc < 3 ){
		printf("Debe ingresar IP del servidor y puerto de escucha !!!\n");	
		return 1;	
	}
	
	//Crear el socket del cliente
	if((x=socket(AF_INET,SOCK_STREAM,0))==-1){	
		printf("No se pudo crear el socket !!!\n");	
		return 1;
	}

	//argv[0]->Nombre del ejecutable
	//argv[1]->IP
	//argv[2]->Puerto	
	bzero((char *) &sa, sizeof(struct sockaddr_in));
 	sa.sin_family		=	AF_INET;
 	sa.sin_port			=	htons(atoi(argv[2]));
	sa.sin_addr.s_addr=	inet_addr(argv[1]);

	//Solicitud de conexión
	if(connect(x,(struct sockaddr *) &sa,sizeof(sa))==-1){
		printf("Solicitud rechazada !!!\n");	
		return 1;
	}

	printf("BIENVENIDO\nTIPEE LAS SIGUIENTES PALABRAS Y PRESIONE ENTER\n");	
	
	for(int i=0;i<3;i++)
 	{
	bzero(buffer,256);
	recv(x,buffer,256,0);
  	printf("%s\n",buffer);
	
	scanf("%s",buffer);
	send(x,buffer,strlen(buffer),0);

	bzero(buffer,256);
	recv(x,buffer,256,0);
  	printf("%s",buffer);

	}

	bzero(buffer,256);
	recv(x,buffer,256,0);
  	printf("%s",buffer);

 	close(x);
 	return 0;
}
