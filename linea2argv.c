#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minish.h"

//#define MAXWORD 1024

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
		//	wp = word;
			if( *word != '<' && *word != '>' ){
				*argv = strdup(word);
				word_finded++;
				argv++;
			} else {
				if( io_set(word) != 0 ){
					return -1;	
				} 	
			}
		
		} else if( c != ' ' ) {
			if( in_word ){
				*wp++ = c;
			} else {
				wp = word;
				*wp++ = c;
				in_word = 1;
			}
		}

	}
	if( c == '\n' && in_word ) {
		*wp = '\0';

		if( *word != '<' && *word != '>' ){
			*argv++ = strdup(word);
			word_finded++;
		} else {
			if( io_set(word) != 0 ){
				return -1;	
			} 	
		}
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

