

#include <stdlib.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int
builtin_pid(int argc, char *argv[])
{
	int s;

	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
	
		errno = E2BIG;
		return errno;
	}

	printf("PID: %d\n", getpid());



	return EXIT_SUCCESS;
}

