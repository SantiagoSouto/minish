#include "minish.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1024
#define ENDSTR "FIN\n"
#define MAXARG 100

#define HELP_CD      "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR     "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT    "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP    "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid]"
#define HELP_HISTORY "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV  "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID     "pid - muestra Process Id del minish"
#define HELP_SETENV  "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS  "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID     "uid - muestra nombre y número de usuario dueño del minish"

struct builtin_struct builtin_arr[] = {
{ "uid", builtin_uid, HELP_UID },
{NULL, NULL, NULL}
};

int
main(void)
{
	int argc, cmd_argc, result;
	char *argv[MAXARG];
	argc = MAXARG;
//	char **argvp;

	char *user_name, *directory; 
	char line[MAXLINE];
	char endstr[] = ENDSTR;
	
	user_name = strdup(getenv("USER"));
	directory = strdup(getenv("PWD"));
	
	fprintf(stderr, "(minish) (%s):%s > ", user_name, directory);

	while( fgets(line, MAXLINE, stdin) != NULL ) {
		
		if( strcmp(line, endstr) == 0 ){
			break;
		}
		
		cmd_argc = linea2argv(line, argc, argv);
/*
		
		argvp = argv;

		printf("%d\n", cmd_argc);

		while( *argvp != NULL ){
			printf("%s\n", *argvp++);
		}
*/
		result = ejecutar(cmd_argc, argv);

		printf("Exit status: %d\n", result);

		fprintf(stderr, "(minish) (%s):%s > ", user_name, directory);
	}
	
	printf("\n");
	exit(EXIT_SUCCESS);
}	

