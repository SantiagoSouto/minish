#include <string.h>
#include <stdlib.h>

#include "minish.h"



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




int
ejecutar(int argc, char **argv)
{


//	if( argc == 0 ) {

		//fprintf(stderr, "Error, no hay comandos a ejecutar!\n");
		//errno = EINVAL;
	//	return 0;    
//	}


	int result = 0;
	struct builtin_struct *function = builtin_lookup(*argv);

	if( function->func != NULL ){
		result = function->func(argc, argv);
	
	} else{
		result = externo(argc, argv);

	}

	return result;



}


