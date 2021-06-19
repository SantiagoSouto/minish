#include <string.h>
#include <stdlib.h>

#include "minish.h"


//Funcion que busca builtin en el array de builtin por nombre
extern struct builtin_struct *builtin_lookup(char *cmd) {

	extern struct builtin_struct builtin_arr[];
	struct builtin_struct *result = builtin_arr;
	char *cmd_name;

	while( (cmd_name = result->cmd) != NULL ){
		if( strcmp(cmd, cmd_name) == 0 ){
			break;
		}
		result++;
	}
	return result;

}



//Funcion que ejecuta un comando
int
ejecutar(int argc, char **argv)
{


	int result = 0;
	struct builtin_struct *function = builtin_lookup(*argv);
	
	//Se encontro funcion. Es interna. Se ejecuta runcion
	if( function->func != NULL ){
		result = function->func(argc, argv);
	
	} else{
		//No se encontro funcion. Se asume que es externa. Se intnta ejecutar
		result = externo(argc, argv);

	}

	return result;



}


