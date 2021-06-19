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
	
	//Recorre una linea caracter a caracter y separa la linea en un array de palabras con una cantidad maxima de argc palabras
	while( ((c=*linea++) != '\n') && (word_finded < argc) ){
		//Estaba leyendo una palabra y llego un espacio
		if( c == ' ' && in_word) {
			in_word = 0;
			*wp = '\0';
			if( *word != '<' && *word != '>' ){
				//Se agrega la palabra a la lista de palabras encontradas
				*argv = strdup(word);
				word_finded++;
				argv++;
			} else {

			//Si el primer caracter de la palabra es un comando de redireccion de entrada/salida, no se agrega a argv. Por el contrario, se atiende la redireccion
				if( io_set(word) != 0 ){
					return -1;	
				} 	
			}
		
		} else if( c != ' ' ) { //Encuentro un caracter que no es espacio
			if( in_word ){
				//Ya estaba dentro de una palabra. Lo agrego a la palabra
				*wp++ = c;
			} else {
				//Es el primer caracter de la palabra
				wp = word;
				*wp++ = c;
				in_word = 1;
			}
		}

	}

	///Analogo al while pero [ara la ultima palabra de la linea
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
