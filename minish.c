#include "minish.h"


FILE *base_stdin;
FILE *base_stdout;

int reset_in_needed = 0;
int reset_out_needed = 0;
int globalstatret = 0;
int minish_run = 1;

struct list *history = NULL;
struct listnode *use_cmd = NULL;

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
{ "exit", builtin_exit, HELP_EXIT },
{ "help", builtin_help, HELP_HELP },
{NULL, NULL, NULL}
};
//Varibale para guardar el directorio local
char directory[MAXWORDS];

//Resetea el stdout y stdin e imprime el prompt
void print_prompt(char *user) {
	io_reset();
	getcwd(directory, MAXWORDS);
	printf("(minish) (%s):%s> ", user, directory);
}

int main(void) {

	signal(SIGINT, interrupt_ctrl_c);

	int argc, cmd_argc;
	char *argv[MAXARG];
	argc = MAXARG;


	char *user_name; 
	char line[MAXLINE];
	char endstr[] = ENDSTR;
	
	//Se deifne el username. se asume que no se cambia de username durante la ejecucion del programa
	user_name = strdup(getenv("USER"));

	while(minish_run) {
		print_prompt(user_name);
		
		if(fgets(line, MAXLINE, stdin) == NULL) {
			break;
		}
		
		//Se incluye um comando especial de salida
		if(strcmp(line, endstr) == 0) {
			break;
		}
		//Guarda la liena recien leida
		if (save_history(line)) {
			exit(EXIT_FAILURE);
		}
		//castea la line a argv
		cmd_argc = linea2argv(line, argc, argv);
		if(cmd_argc > 0) {
			//ejecuta el comnado en base a lo que se almaceno en argvv y devuelve el status del comando
			globalstatret = ejecutar(cmd_argc, argv);
		
		
		}		
		//Cheuqea la existencia de errores en la ejecucion de los comandos
		if(globalstatret != 0 || cmd_argc < 0) {
			fprintf(stderr, "Error with commnad %s!\n%s\n", *argv, strerror(errno));
	
	
		}
	}
	//Escribe el archivo log de lineas
	if (write_history()) {
		exit(EXIT_FAILURE);
	}
	
	//Realiza el exit del minishell
	exit_status();
	exit(EXIT_SUCCESS);
}
