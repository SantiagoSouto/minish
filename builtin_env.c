#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <string.h>

//Devuelve variables de amiente
int builtin_getenv (int argc, char **argv) {
	if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}
	char **allEnv; // when every env variable is asked
	char *env; 
	switch (argc) {
		case 1:
			Devuelve todas la variables
			allEnv = __environ; 
			for (; *allEnv != NULL; allEnv++) {
				printf("%s\n", *allEnv);
			}
			break;
		default:
			//Devuelve las variables solicitadas
			for (++argv; *argv != NULL; ++argv) {
				//Itera por variable y devuelve cada una 
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

//Seta variables de ambiente
int builtin_setenv (int argc, char **argv) {
	if(argc != 3){

		fprintf(stderr, "Usage: %s [name] [value]\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *env = *(++argv);
	char *val = *(++argv);

	//Setea la variable si es posible. Sobreescribe si ya existia
	int status = setenv(env, val, 1);
	if (status != 0) {
		//printf( "Error agregando variable de entorno.\nUso: setenv [nombre] [valor]\n");
		return errno;
	}


	return EXIT_SUCCESS;
}

//Borra una variable previamente sereada
int builtin_unsetenv (int argc, char ** argv) {
	if (argc < 1) {
	    printf( "No hay argumentos suficientes\n");
	    return 1;
	}
	
	int status;

	switch (argc) {
		case 1:
			//No se especifica la variable a borrar
			fprintf(stderr, "Usage: %s [var..]\n", argv[0]);
			return EXIT_FAILURE;
		default:
			//Se itrea y se borra una por una 
			for (++argv; *argv != NULL; argv++) {
				status = unsetenv(*argv);
				if (status != 0) {
					fprintf(stderr, "Error al eliminar variable %s.\n", *argv);
				}
			}
	}
	return EXIT_SUCCESS;
}
