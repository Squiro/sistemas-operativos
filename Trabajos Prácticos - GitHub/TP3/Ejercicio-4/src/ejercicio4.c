#include "funciones.h"


/*# =========================== Encabezado =======================

# Nombre del archivo: ejercicio4.c
# Número de ejercicio: 4
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
    } else
    {
        // Primero se crea el area de memoria compartida, y el puntero es enviado
        // como parametro a la funcion
        int shmid; 
        leerConsultas(crearSHM(&shmid));
    }
}