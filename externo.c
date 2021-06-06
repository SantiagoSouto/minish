#include "minish.h"

int externo(int argc, char **argv) {

	pid_t child_process;

	child_process = fork();
	int wstatus;
	switch (child_process) {
		case -1:
//			fprintf(stderr, "Error al ejecutar el comando %s!\n", *argv);
			return errno;
		case 0:
			execvp(*argv, argv);
//			fprintf(stderr, "Error al ejecutar el comando %s!\n", *argv);
			fprintf(stderr, "%s: command not found!\n", *argv);
			exit(EXIT_FAILURE);
		default:
			while (wait(&wstatus) != child_process){
				;
			}
			break;
	}

	return 0;

}
