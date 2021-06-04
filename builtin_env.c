#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <string.h>

//#include "minish.h"

int builtin_getenv (int argc, char **argv) {
	if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}
	char **allEnv; // when every env variable is asked
	char *env; 
	switch (argc) {
		case 1:
			allEnv = __environ; 
			for (; *allEnv != NULL; allEnv++) {
				printf("%s\n", *allEnv);
			}
			break;
		default:
			for (++argv; *argv != NULL; ++argv) {
				env = getenv(*argv);
				if (env == NULL) {
					printf("env %s: No se encuentra definida.\n", *argv);
				} else {
					printf("%s=%s\n", *argv, env);
				}
			}
	}
	return EXIT_SUCCESS;
}

int builtin_setenv (int argc, char **argv) {
	if(argc != 3){ 
		printf( "Cantidad de argumentos no coincide.\nUso: setenv [nombre] [valor]\n");
		return 1;
	}

	char *env = *(++argv);
	char *val = *(++argv);

	int status = setenv(env, val, 1);
	if (status != 0) {
		printf( "Error agregando variable de entorno.\nUso: setenv [nombre] [valor]\n");
		return 2;
	}


	return EXIT_SUCCESS;
}

int builtin_unsetenv (int argc, char ** argv) {
	if (argc < 1) {
	    printf( "No hay argumentos suficientes\n");
	    return 1;
	}
	
	int status;

	switch (argc) {
		case 1:
			printf( "No se especifican variables a eliminar.\nUso: unsetenv [var..]\n");
			return 1;
			//break;
		default:
			for (++argv; *argv != NULL; argv++) {
				status = unsetenv(*argv);
				if (status != 0) {
					fprintf(stderr, "Error al eliminar variable %s.\n", *argv);
				}
			}
	}
	return EXIT_SUCCESS;
}
