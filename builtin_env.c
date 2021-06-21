#include "minish.h"

int builtin_getenv (int argc, char **argv) 
{
	/*
     * 
     * Función que imprime variables de entorno. Ya sea todas 
	 * las del sistema o la cantidad especificada por los argumentos
	 * agregados.
     * 
    */

   	// Verifica que se tenga algún argumento
	if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}
	// Cuando todas las variables se piden
	char **allEnv;
	// Cuando se pide una cantidad acotada
	char *env; 
	// Según la cantidad de argumentos, depende lo que se imprime
	switch (argc) {
		case 1:
			//Devuelve todas la variables
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


int builtin_setenv (int argc, char **argv) 
{
	/*
     * 
     * Función que setea variables de entorno. Es importante
	 * verificar que se setee de a una variable por vez.
     * 
    */

   	// Verifica que se tengan exactamente tres argumentos (uno "setenv" y la llave-valor)
	if(argc != 3){

		fprintf(stderr, "Usage: %s [name] [value]\n", argv[0]);
		return EXIT_FAILURE;
	}

	// El primer argumento es el nombre de la variable (llave)
	char *env = *(++argv);
	// El segundo argumento es el valor de dicha variable (valor)
	char *val = *(++argv);

	//Setea la variable si es posible. Sobreescribe si ya existia
	int status = setenv(env, val, 1);
	if (status != 0) {
		//printf( "Error agregando variable de entorno.\nUso: setenv [nombre] [valor]\n");
		return errno;
	}

	return EXIT_SUCCESS;
}


int builtin_unsetenv (int argc, char ** argv) 
{
	/*
     * 
     * Función que borra aquellas variables de entorno especificadas 
	 * por los argumentos agregados.
     * 
    */

   	// Verifica que se tenga algún argumento
	if (argc < 1) {
	    printf( "No hay argumentos suficientes\n");
	    return 1;
	}
	
	// Variable para verificar el estado de cada borrado
	int status;

	// Se deben pasar al 2 arguementos, con los nombres de las "llaves" a eliminar
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
