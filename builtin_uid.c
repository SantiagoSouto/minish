#include "minish.h"

int builtin_uid(int argc, char *argv[])
{
	/*
     * 
     * Función que muestra la información del
	 * usuario y dueño del programa.
     * 
    */

	struct passwd pwd;
	struct passwd *result;
	char *buf;
	int bufsize;
	int s;
	
	// Verifica que se tenga la cantidad adecuada de argumentos
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
		return errno;
	}
	
	//Busca el nombre de usuario. Atiende errores en caso de que el usuario no exista o no se pueda completar la operacion
	s = getpwnam_r(getenv("USER"), &pwd, buf, bufsize, &result);
	if (result == NULL) {
		if (s == 0)
			printf("Not found\n");
		else {
			errno = s;
			perror("getpwnam_r");
		}
		return errno;
	}

	printf("Name: %s; UID: %ld\n", pwd.pw_gecos, (long) pwd.pw_uid);
	free(buf);

	return EXIT_SUCCESS;
}

