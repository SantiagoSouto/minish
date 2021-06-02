

#include <stdlib.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int
builtin_cd(int argc, char *argv[])
{
	int result;
	char *dir;
	char back[] = "../";

	if (argc > 2) {
		fprintf(stderr, "Usage: %s [dir]\n", argv[0]);
		return EXIT_FAILURE;
	}

	if( argc == 1 ){
		dir = getenv("HOME");
	}	

	if( argc == 2 ){
		if( strcmp("-", *(argv+1)) == 0 ){
			dir = back;
		} else{
			dir = *(argv+1);
		}
	}

	result = chdir(dir);	


	return result;
}

