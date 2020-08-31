#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CONSULTA 512

void ayuda();
void error(char *);

void main(int argc, char *argv[]) {
	if (argc > 1) {
		if (strcmp(argv[1],"-help") == 0) {
			ayuda();
		}

		if (argc == 3) {
			char respuesta[TAM_CONSULTA];
			char consulta[TAM_CONSULTA];
			int clientSocket;
			struct sockaddr_in serverAddress;

			clientSocket = socket(AF_INET, SOCK_STREAM, 0);
			
			if (clientSocket == -1) {
				error("No se pudo crear el socket.");
				exit(1);
			}

			memset(&serverAddress, 0, sizeof(struct sockaddr_in));
			serverAddress.sin_family = AF_INET;
			serverAddress.sin_port = htons(atoi(argv[2]));
			serverAddress.sin_addr.s_addr = inet_addr(argv[1]);

			if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
				error("No se pudo conectar con el servidor");
				exit(1);
			}

			printf("Escriba una consulta: \n");
			scanf("%s", consulta);
			int len;

			while (strcmp(consulta, "QUIT") != 0) {
				send(clientSocket, consulta, sizeof(consulta), 0);

				recv(clientSocket, respuesta, sizeof(int), 0);
				len = atoi(respuesta);
				recv(clientSocket, respuesta, len, 0);	
				//strcpy(respuesta, "Procesando...");
				
				while (strcmp(respuesta,"ENDOFTHELINE") != 0) {
					printf("RESPUESTA: %s\n", respuesta);
					memset(respuesta, 0, strlen(respuesta));
					recv(clientSocket, respuesta, sizeof(int), 0);
					len = atoi(respuesta);
					recv(clientSocket, respuesta, len, 0);		
				}

				printf("Escriba una consulta: \n");
				scanf("%s", consulta);
			}
			
			send(clientSocket, consulta, sizeof(consulta), 0);
			close(clientSocket);
		} else {
			error("Este programa necesita recibir por parámetro la IP y el puerto.");
		}
	} else {
		ayuda();	
	}		
	
	
}

void error(char *msg) {
    printf("%s\n\n", msg);
}

void ayuda() {
    printf("\n\n");
    printf("Este programa realiza consultas hacia un proceso demonio para\n");
    printf("obtener datos sobre un archivo.\n\n");
    printf("Recibe como parámetros la IP donde se está ejecutando el proceso demonio.\n");
    printf("y el puerto en donde el mismo escucha.\n\n");
    printf("Sintaxis de ejecución: \n");
    printf("./cliente <ip> <puerto>\n");
}