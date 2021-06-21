#include "minish.h"

int builtin_pid(int argc, char *argv[])
{
	/*
     * 
     * Función que muestra el process ID (PID) del
	 * usuario.
     * 
    */
	
	// Verifica que se tenga la cantidad adecuada de argumentos
	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
	
		errno = E2BIG;
		return errno;
	}

	// Obtiene e imprime el pid
	printf("PID: %d\n", getpid());

	return EXIT_SUCCESS;
}

