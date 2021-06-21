#include "minish.h"

int builtin_help (int argc, char **argv) 
{
	/*
     * 
     * Función que imprime los textos de ayuda según el argumento
	 * con la función especificada. En caso de no especificar ninguna 
	 * función, se imprimirán las funciones internas disponibles.
     * 
    */

	// Verifica que se tenga algún argumento
	if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}

	struct builtin_struct *func;

	//Dependiendo de la cantidad de argumentos que tipo de ayuda imprime
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
			fprintf(stderr, "Usage: %s [command]\n", argv[0]);
			errno = E2BIG;
			return errno;
	}

	return EXIT_SUCCESS;
}
