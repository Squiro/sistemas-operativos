#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {

	/*sem_t *mutexMemoria = sem_open("/mutexMemoria", O_CREAT, 0666, 1);
    sem_t *hayConsulta = sem_open("/hayConsulta", O_CREAT, 0666, 0);
    sem_t *hayRespuesta = sem_open("/hayRespuesta", O_CREAT, 0666, 0);

    sem_close(mutexMemoria);
    sem_close(hayConsulta);
    sem_close(hayRespuesta);*/
	sem_unlink("/mutexMemoria");
	sem_unlink("/hayConsulta");
	sem_unlink("/hayRespuesta");
	sem_unlink("/puedeConsultar");
	sem_unlink("/puedeEnviar");
}