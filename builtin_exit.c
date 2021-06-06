#include "minish.h"

int builtin_exit (int argc, char **argv) {

    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}

    minish_run = 0;

    switch (argc) {
        case 1:
            return EXIT_SUCCESS;
        case 2:
            return atoi(*(++argv));
        default:
            return EXIT_FAILURE;
    }
}