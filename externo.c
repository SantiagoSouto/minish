#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

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
			return errno;
		default:
			while (wait(&wstatus) != child_process){
				;
			}
			break;
	}

	return 0;

}
