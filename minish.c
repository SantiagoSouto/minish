#include "minish.h"


FILE *base_stdin;
FILE *base_stdout;

int reset_in_needed = 0;
int reset_out_needed = 0;
int globalstatret = 0;
int minish_run = 1;

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
{ "exit", builtin_exit, HELP_EXIT },
{ "help", builtin_help, HELP_HELP },
{NULL, NULL, NULL}
};

char directory[MAXWORDS];

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

	if (get_history()) {
		exit(EXIT_FAILURE);
	}

	int argc, cmd_argc;
	char *argv[MAXARG];
	argc = MAXARG;

	char *user_name; 
	char line[MAXLINE];
	char endstr[] = ENDSTR;
	
	user_name = strdup(getenv("USER"));
//	print_prompt(user_name);

	while(minish_run) {
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

	if (write_history()) {
		exit(EXIT_FAILURE);
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
