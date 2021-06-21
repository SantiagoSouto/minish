#include "minish.h"

int externo(int argc, char **argv) 
{
	/*
     * 
     * Función que ejecuta un comando externo. Hace un fork, 
	 * para no perder la ejecución del programa minish y con
	 * el proceso hijo, ejecuta el comando externo.
     * 
    */

   	// Verifica que se tenga algún argumento
	if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}

	pid_t child_process;

	//Crea un nuevo proceso con el fork
	child_process = fork();
	int wstatus;
	switch (child_process) {
		case -1:
			//Error en fork
			return errno;
		case 0:
			execvp(*argv, argv);
			//El execvp falla
			//En caso del que comando no se encietre se atiende el error. De lo contrario el error se atiende por el comando
			fprintf(stderr, "%s: command not found!\n", *argv);
			//Se termina el proceso hijo
			exit(EXIT_FAILURE);
		default:
			while (wait(&wstatus) != child_process){
				;
			}
			break;
	}

	return EXIT_SUCCESS;
}
