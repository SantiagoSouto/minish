#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "minish.h"

int
linea2argv(char *linea, int argc, char **argv)
{
	int in_word = 0;
	char word[MAXWORDS];
	char *wp = word;
	char c;
	int word_finded = 0;
	

	while( ((c=*linea++) != '\n') && (word_finded < argc) ){
		if( c == ' ' && in_word) {
			in_word = 0;
			*wp = '\0';
			*argv = strdup(word);
			argv++;
		
		} else if( c != ' ' ) {
			if( in_word ){
				*wp++ = c;
			} else {
				wp = word;
				*wp++ = c;
				in_word = 1;
				word_finded++;
			}
		}

	}
	if( (c == '\n') && in_word && (word_finded < argc) ) {
		*wp = '\0';
		*argv = strdup(word);
		argv++;
	}
	
	*argv = NULL;

	return word_finded;

}


/*
int
main(void)
{
	int argc = 100;
	char *argarray[argc];
	char **argv = argarray;
	char line[] = "arguno argdos -arg3";
	char *lp = line;


	int argnum = line2argv(line, argc, argv);
	int i = 0;
	while( argnum-- > 0 ){

		printf("%d: %s\n", i++, *argv);
		argv++;
	}
	
}


*/

