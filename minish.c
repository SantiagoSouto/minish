#include "minish.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1024
#define ENDSTR "FIN\n"


#define HELP_CD      "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR     "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT    "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP    "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid]"
#define HELP_HISTORY "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV  "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID     "pid - muestra Process Id del minish"
#define HELP_UNSETENV  "unsetenv var [var] - elimina el valor de variable de ambiente"
#define HELP_SETENV  "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS  "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID     "uid - muestra nombre y número de usuario dueño del minish"
#define HELP_GID     "gid - muestra el grupo principal y los grupos secundarios del usuario dueño del minish"


FILE *base_stdin;
FILE *base_stdout;

int reset_in_needed = 0;
int reset_out_needed = 0;
int globalstatret = 0;

struct stack *history = NULL;

struct builtin_struct builtin_arr[] = {
{ "cd", builtin_cd, HELP_CD },
{ "uid", builtin_uid, HELP_UID },
{ "pid", builtin_pid, HELP_PID },
{ "gid", builtin_gid, HELP_GID },
{ "dir", builtin_dir, HELP_DIR },
{ "status", builtin_status, HELP_STATUS },
{ "setenv", builtin_setenv, HELP_SETENV },
{ "getenv", builtin_getenv, HELP_GETENV },
{ "unsetenv", builtin_unsetenv, HELP_UNSETENV },
{ "history", builtin_history, HELP_HISTORY },
{NULL, NULL, NULL}
};

char directory[MAXWORDS];

char *get_timestamp() {
    
	char *timestamp = (char *)malloc(sizeof(char));
	time_t *current_time = malloc(sizeof(time_t));
	time(current_time);
	if (*current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
        return NULL;
    }
	struct tm *tm;
	tm = localtime(current_time);
    
    sprintf(timestamp,"%s%04d-%02d-%02d %s%02d:%02d:%02d", "\033[0;32m", tm->tm_year+1900, tm->tm_mon, 
    tm->tm_mday, "\033[0m", tm->tm_hour, tm->tm_min, tm->tm_sec);

    if (timestamp == NULL)
    {
        printf("Error al convertir el tiempo a formato timestamp.\n");
        return NULL;
    }
    return timestamp;
}

int save_history(char *line) {
	char *timestamp = get_timestamp();
	if (timestamp == NULL) {
		return 1;
	}

	if (history == NULL) {
		history = stack_create();
	}

	stack_push(history, timestamp, line);
	return 0;

}

void print_prompt(char *user) {
	io_reset();
	//char directory[MAXWORDS];
	getcwd(directory, MAXWORDS);
	printf("(minish) (%s):%s> ", user, directory);
}

int main(void) {
//	printf("HOLA, %d\n", fileno(stdin));
//	base_stdin = stdin;
//	base_stdout = stdout;

	int argc, cmd_argc;
	char *argv[MAXARG];
	argc = MAXARG;

	char *user_name; 
	char line[MAXLINE];
	char endstr[] = ENDSTR;
	
	user_name = strdup(getenv("USER"));
//	print_prompt(user_name);

	while( 1 ) {
		print_prompt(user_name);
		
//		getcwd(directory, MAXWORDS);
//		fprintf(stdout, "(minish) (%s):%s> ", user_name, directory);
		if( fgets(line, MAXLINE, stdin) == NULL ){
			break;
		}

		if( strcmp(line, endstr) == 0 ){
			break;
		}
		
		if (save_history(line)) {
			exit(EXIT_FAILURE);
		}
		cmd_argc = linea2argv(line, argc, argv);
		if( cmd_argc > 0 ){
	
			globalstatret = ejecutar(cmd_argc, argv);
		
		
//			io_reset(argv);	
//			printf("Exit status: %d\n", globalstatret);
		}		
		if( globalstatret != 0 || cmd_argc < 0){
			fprintf(stderr, "Error with commnad %s!\n%s\n", *argv, strerror(errno));
	
	
		}	
//		print_prompt(user_name);
	}
	
	printf("\n");
	exit(EXIT_SUCCESS);

}


/*
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

		
		argvp = argv;

		printf("%d\n", cmd_argc);

		while( *argvp != NULL ){
			printf("%s\n", *argvp++);
		}

		result = ejecutar(cmd_argc, argv);

//		printf("Exit status: %d\n", result);

		fprintf(stderr, "(minish) (%s):%s > ", user_name, directory);
	}
	
	printf("\n");
	exit(EXIT_SUCCESS);
}	
*/
