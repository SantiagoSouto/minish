#include "minish.h"

int builtin_exit (int argc, char **argv) {

	if( argc < 1 ){

		fprintf(stderr, "Usage: %s [command]\n", argv[0]);
		errno = E2BIG;
		return errno;
	}

	minish_run = 0;
	//Calcula el status de salida segun los argumentos
	switch (argc) {
		case 1:
			return EXIT_SUCCESS;
		case 2:
			return atoi(*(++argv));
		default:

			fprintf(stderr, "Usage: %s [exit_status]\n", argv[0]);
			return EXIT_FAILURE;
	}
}
