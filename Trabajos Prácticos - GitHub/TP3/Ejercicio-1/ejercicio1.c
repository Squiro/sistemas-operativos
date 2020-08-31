#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*# =========================== Encabezado =======================

# Nombre del archivo: ejercicio1.c
# Número de ejercicio: 1
# Trabajo Práctico: 3
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
#					|						|
# -------------------------------------------------------------*/
void error();
void mostrarInfo(int, int, char *, char *);
void ayuda();


void main(int argc, char *argv[]) {
    if (argc > 1) {
    	if (strcmp(argv[1],"-help") == 0)
        	ayuda();
    }
    else {

        mostrarInfo(getpid(), getppid(), "Soy el padre", "Normal");

        // Guardamos los PIDS de los hijos
        int hijo1 = fork();

        if (hijo1 == -1) {
            error();
            exit(1);
        } 

        if (hijo1 == 0) {
            mostrarInfo(getpid(), getppid(), "Soy el primer hijo", "Demonio");
            //Creamos al primer bisnieto y primer zombie
            int zombie1 = fork();

            if (zombie1 == -1) {
                error();
                exit(1);
            }

            if (zombie1 == 0) {
                mostrarInfo(getpid(), getppid(), "Soy el primer nieto", "Zombie");
                int bisnieto1 = fork();

                if (bisnieto1 == -1) {
                    error();
                    exit(1);
                }

                if (bisnieto1 == 0) {
                    mostrarInfo(getpid(), getppid(), "Soy el primer bisnieto", "Normal");
                    getchar();
                }

                int bisnieto2 = fork();

                if (bisnieto2 == -1) {
                    error();
                    exit(1);
                }

                if (bisnieto2 == 0) {
                    mostrarInfo(getpid(), getppid(), "Soy el segundo bisnieto", "Normal");
                    getchar();
                }

                getchar();
                wait(NULL);
                wait(NULL);
                exit(0);
            }

            //Segundo nieto, segundo zombie
            int zombie2 = fork();

            if (zombie2 == -1) {
                error();
                exit(1);
            } 

            if (zombie2 == 0) {
                mostrarInfo(getpid(), getppid(), "Soy el segundo nieto", "Zombie");
                
                int bisnieto3 = fork();

                if (bisnieto3 == -1) {
                    error();
                    exit(1);
                }

                if (bisnieto3 == 0) {
                    mostrarInfo(getpid(), getppid(), "Soy el tercer bisnieto", "Normal");
                    getchar();
                }

                int bisnieto4 = fork();

                if (bisnieto4 == -1) {
                    error();
                    exit(1);
                }

                if (bisnieto4 == 0) {
                    mostrarInfo(getpid(), getppid(), "Soy el cuarto bisnieto", "Normal");
                    getchar();
                }

                getchar();
                wait(NULL);
                wait(NULL);
                exit(0);
            }

            while(1) {
                //Demonizado
            }
        }

        int hijo2 = fork();

        if (hijo2 == -1) {
            error();
            exit(1);
        }

        if (hijo2 == 0) {
            mostrarInfo(getpid(), getppid(), "Soy el segundo hijo", "Normal");

            int nieto3 = fork();

            if (nieto3 == -1) {
                error();
                exit(1);
            }

            if (nieto3 == 0) {
                mostrarInfo(getpid(), getppid(), "Soy el tercer nieto", "Demonio");

                int bisnieto5 = fork();

                if (bisnieto5 == -1) {
                    error();
                    exit(1);
                }

                if (bisnieto5 == 0) {
                    mostrarInfo(getpid(), getppid(), "Soy el quinto bisnieto", "Normal");
                    getchar();
                }
            
                wait(NULL);

                while (1) {
                    // Demonizado
                }
            }

            wait(NULL);
        }

        //printf("Presione una tecla para contiunuar\n");
        getchar();
    }

}

void error() {
    printf("Pasó algo muy feo y todavía no sabemos por qué. :(\n\n");
}

// Muestra info del proceso en sí
void mostrarInfo(int pid, int ppid, char *parentesco, char *tipo) {
    printf("PID: %d PPID: %d Parentesco-Tipo: %s - %s\n\n", pid, ppid, parentesco, tipo);
}

void ayuda() {
    printf("\n\n");
    printf("Este script crea una jerarquía de hijos, nietos, y bisnietos. Algunos de esos procesos\n");
    printf("quedan en estado zombie, otros en estado demonio.\n");
    printf("Todos los procesos quedan a la espera de getchar(), para que se pueda ver la jerarquía creada con un ps -aux.\n");

    printf("Para ver la ayuda, ejecute ./ejercicio1 -help\n");
}