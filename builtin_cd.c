#include "minish.h"

#include <stdlib.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int
builtin_cd(int argc, char *argv[])
{
	int status;
	int result;
	char *dir;
	char oldpwd[MAXWORDS];
	char directory[MAXWORDS];
	char *o_pwd;




	//Chequea cnatida de argumentos correcta	
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [dir]\n", argv[0]);
		errno = E2BIG;	
		return errno;
	}

	//Resuelve directorio nuevo
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

