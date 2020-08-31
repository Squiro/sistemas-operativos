#include "funciones.h"


/*# =========================== Encabezado =======================

# Nombre del archivo: ejercicio5.c
# Número de ejercicio: 5
# Trabajo Práctico: 3
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
#					|						|
# -------------------------------------------------------------*/

void main(int argc, char *argv[]) {

    if (argc > 1) {
        // Chequeamos si se recibio un parametro de ayuda
        if (strcmp(argv[1],"-help") == 0) {
            ayuda();
        }    
        else
        {
            int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

            if (serverSocket == -1) {
                error("No se pudo crear el socket.");
                exit(1);
            }

            // Seteo de opciones del socket
            if (configurarOpciones(serverSocket) < 0)
            {
                error("No se pudo configurar las opciones del socket.");
                exit(1);
            }

            // Seteo de la config del socket, se le envia el primer argumento
            // como parametro (el puerto)
            struct sockaddr_in serverAddress = configurarSocket(argv[1]);

            // Binding del socket con la config
            if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr_in)) < 0)
            {
                error("No se pudo vincular el socket con la configuración del servidor.");
                exit(1);
            }
           
            // Ponemos el socket en modo escucha
            listen(serverSocket, MAX_QUEUE);

            // Acepta conexiones de sockets clientes
            aceptarConexionesEntrantes(serverSocket);
        }        
    }
    else {
        error("Este programa necesita recibir como parámetro el puerto de escucha.");
        ayuda();
    } 
}