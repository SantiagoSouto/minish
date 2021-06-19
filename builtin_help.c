#include "minish.h"

int builtin_help (int argc, char **argv) {

	//Chequea canidad correcta de args
	if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}

	struct builtin_struct *func;

	//Depedniendo de la cantidad de argumentos que tipo de ayuda imprime
	switch (argc) {
		case 1:
			printf("%s\n", HELP_HELP);
			break;
		case 2:
			//Busca la funcion que se paso como argumento entre todas las funciones built_in
			if ((func = builtin_lookup(*(++argv)))->func != NULL) {
				printf("%s\n", func->help_txt);
				break;
			} else {
				printf("Comando interno no existe.\n");
				return 1;
			}
		default:
		//	printf("Muchos argumentos.\nUso: help [comando]\n");
			fprintf(stderr, "Usage: %s [command]\n", argv[0]);
			errno = E2BIG;
			return errno;
		//	return 1;
	}

	return 0;
}
