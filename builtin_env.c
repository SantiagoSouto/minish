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
	char *env; 
	switch (argc) {
		case 1:
			for (; *__environ != NULL; __environ++) {
				printf("%s\n", *__environ);
			}
			break;
		default:
			//env = malloc(sizeof(char));
			for (++argv; *argv != NULL; argv++) {
				env = strdup(getenv(*argv));
				if (env == NULL) {
					printf("env %s: No se encuentra definida.\n", *argv);
				} else {
					printf("%s\n", env);
				}
			}
			free(env);
	}
	return EXIT_SUCCESS;
}

int builtin_setenv (int argc, char ** argv) {
	if(argc != 3){ 
		printf( "Cantidad de argumentos no coincide.\nUso: setenv [nombre] [valor]\n");
		return 1;
	}
	//    const char *env = strdup(*(++argv));
	//    const char *val = strdup(*(++argv));
	//

	//env = strdup(*(++argv));
	//val = strdup(*(++argv));

	//    printf("%s, %s\n", env, val);
	int status = setenv(*(++argv), *(++argv), 1);
	//int status = setenv(env, val, 1);
	if (!status) {
		printf( "Error agregando variable de entorno.\nUso: setenv [nombre] [valor]\n");
		return 2;
	}


	return EXIT_SUCCESS;
}

int builtin_unsetenv (int argc, char ** argv) {
	/*    if (argc < 1) {
	      printf( "No hay argumentos suficientes\n");
	      return 1;
	      }
	      */
	int status;

	switch (argc) {
		case 1:
			printf( "No se especifican variables a eliminar.\nUso: unsetenv [var..]\n");
			return 1;
			//break;
		default:
			for (++argv; *argv != NULL; argv++) {
				status = unsetenv(*argv);
				if (!status) {
					fprintf(stderr, "Error al eliminar variable %s.\n", *argv);
				}
			}
	}
	return EXIT_SUCCESS;
}
