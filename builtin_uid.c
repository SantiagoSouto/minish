
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int
builtin_uid(int argc, char *argv[])
{
	struct passwd pwd;
	struct passwd *result;
	char *buf;
	size_t bufsize;
	int s;

	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		errno = E2BIG;
		return errno;
	}

	bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
	if (bufsize == -1)          /* Value was indeterminate */
		bufsize = 16384;        /* Should be more than enough */

	buf = malloc(bufsize);
	if (buf == NULL) {
		perror("malloc");
		return EXIT_FAILURE;
	}
	/*
	char *user_name, *directory; 
	char line[MAXLINE];
	char endstr[] = ENDSTR;

	user_name = strdup(getenv("USER"));

	*/       
	s = getpwnam_r(getenv("USER"), &pwd, buf, bufsize, &result);
	if (result == NULL) {
		if (s == 0)
			printf("Not found\n");
		else {
			errno = s;
			perror("getpwnam_r");
		}
		return EXIT_FAILURE;
	}

	printf("Name: %s; UID: %ld\n", pwd.pw_gecos, (long) pwd.pw_uid);

	return EXIT_SUCCESS;
}

