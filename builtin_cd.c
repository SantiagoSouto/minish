#include "minish.h"

int builtin_cd(int argc, char *argv[])
{
	/*
	 *
	 * Función que cambia de directorio segun argumentos que se agregan
	 * Si no se agregan argumentos, se redirige al directorio raíz (HOME),
	 * si se pasa como argumento un "-" se redirige al directorio anterior,
	 * y si se pasa un argumento sin "-" se intenta redirigir al directorio 
	 * de dicho argumento.
	 *
	*/
	int status;
	int result;
	char *dir;
	char oldpwd[MAXWORDS];
	char directory[MAXWORDS];
	char *o_pwd;




	//Chequea cantidad de argumentos correcta	
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [dir]\n", argv[0]);
		errno = E2BIG;	
		return errno;
	}

	//Resuelve directorio a home
	if( argc == 1 ){
		dir = getenv("HOME");
	}	

	if( argc == 2 ){
		if( strcmp("-", *(argv+1)) == 0 ){
		//Resuelve el directorio anterior
		o_pwd = oldpwd;
		o_pwd = strdup(getenv("OLDPWD"));
		dir = o_pwd;
		} else{
			//Resuelve el directorio que se pide
			dir = *(argv+1);
		}
	}

	
	//Almacena el directorio actual como el directorio anterior

	status = setenv("OLDPWD", getcwd(directory, MAXWORDS), 1);
	if (status != 0) {
		return errno;
	}


	//Cambia de directorio
	result = chdir(dir);	
	
	//Actualiza la variable de ambiente del directorio
	status = setenv("PWD", getcwd(directory, MAXWORDS), 1);
	if (status != 0) {
		return errno;
	}

	return result;
}

