#include <stdlib.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int
builtin_pid(int argc, char *argv[])
{
	int s;
	
	//Chequea cantidad correcta de argumnetos
	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
	
		errno = E2BIG;
		return errno;
	}

	//Obtiene el pid
	printf("PID: %d\n", getpid());



	return EXIT_SUCCESS;
}

