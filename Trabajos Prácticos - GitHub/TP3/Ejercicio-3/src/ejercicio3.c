#include "funciones.h"

/*# =========================== Encabezado =======================

# Nombre del archivo: ejercicio3.c
# Número de ejercicio: 3
# Trabajo Práctico: 3
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
# -------------------------------------------------------------*/


void main(int argc, char *argv[]) {

    if (argc > 1) {
        // Chequeamos si se recibio un parametro de ayuda
        if (strcmp(argv[1],"-help") == 0) {
            ayuda();
        } // Chequeamos si se recibio menos que la cantidad necesaria de parametros
        else if (argc < 3) {
            error("Argumentos faltantes. Este script necesita la rutas de ambos FIFOs a crear.");
            ayuda();
        } else {
            // Crea los FIFOS
            crearFIFOS(argv[1], argv[2]);
            leerConsultas(argv[1], argv[2]);
        }     
    } else
    {
        ayuda();
    }
}