#include "minish.h"

int builtin_status(int argc, char *argv[])
{
	/*
     * 
     * Función que muestra el estado del programa.
     * 
    */

	// Verifica que se tenga la cantidad adecuada de argumentos
	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		errno = E2BIG;
		return errno;
	}
	// Imprime el ultimo status de retorno
	printf("Status: %d\n", globalstatret);

	return EXIT_SUCCESS;
}

