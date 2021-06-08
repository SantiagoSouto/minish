#include "minish.h"

int builtin_help (int argc, char **argv) {
    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}

	struct builtin_struct *func;

	switch (argc) {
		case 1:
			printf("%s\n", HELP_HELP);
			break;
		case 2:
			if ((func = builtin_lookup(*(++argv)))->func != NULL) {
				printf("%s\n", func->help_txt);
				break;
			} else {
				printf("Comando interno no existe.\n");
				return 1;
			}
		default:
			printf("Muchos argumentos.\nUso: help [comando]\n");
			return 1;
	}
    
    return 0;
}