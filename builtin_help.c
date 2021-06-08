#include "minish.h"

int builtin_help (int argc, char **argv) {
    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}
    
    return 0;
}