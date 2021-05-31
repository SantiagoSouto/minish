
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

#define MAXLINE 1024
#define ENDSTR "FIN\n"
#define MAXARG 100


int
main(void)
{
	int argc;
	char *argv[MAXAR];
	

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


		fprintf(stderr, "(minish) (%s):%s > ", user_name, directory);
	}
	

	exit(EXIT_SUCCESS);
}	

