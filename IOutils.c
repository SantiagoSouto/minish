#include <stdio.h>
#include "huffman.h"
#include "heap_generic.h"
#include "huffman_func.h"
#include "wrappers.h"
#define BUFFERLEN 8
#define leftmostbit(mask, masklen) ((mask >> (masklen-1)) & 1)

size_t fputbits(int mask, int masklen, FILE *fp) {
	static int buffer[BUFFERLEN];
	static int count;
	int buffer_write = 0;
	while( masklen > 0 ){ 
		for (; count < BUFFERLEN && masklen > 0; count++, masklen--){
			buffer[count] = leftmostbit(mask, masklen) & 1;
		}
		if( count == BUFFERLEN ){
       		for (int i = 0; i < BUFFERLEN; i++) {
            	buffer_write |= buffer[i];
            	buffer_write <<= 1;
       		}
			buffer_write >>= 1;
			fwrite_or_exit(&buffer_write, 1, 1, fp);
			count = 0;
			for (int i = 0; i < BUFFERLEN; i++) {
				buffer[i] = 0;
			}
		}
	}

	return count;
}

size_t freadbits(FILE *fp) {
	static int count;
	static int buffer_read;
	if (count == 0 || count == BUFFERLEN) {
		buffer_read = 0;
		count = 0;
		fread_or_exit(&buffer_read, 1, 1, fp);
	}
	count++;
	return leftmostbit(buffer_read, BUFFERLEN-count+1);

	/*
	for (; count < BUFFERLEN; count++, masklen--){
			buffer[count] = leftmostbit(mask, masklen) & 1;
		}
		if( count == BUFFERLEN ){
       		for (int i = 0; i < BUFFERLEN; i++) {
            	buffer_write |= buffer[i];
            	buffer_write <<= 1;
       		}
			buffer_write >>= 1;
			fwrite_or_exit(&buffer_write, 1, 1, fp);
			count = 0;
			for (int i = 0; i < BUFFERLEN; i++) {
				buffer[i] = 0;
			}
		}
	}

	return count;
	*/
}

/*
int
main(int argc, char *argv[])
{
    char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s string delim subdelim\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int j = 1, str1 = argv[1]; ; j++, str1 = NULL) {
        token = strtok_r(str1, argv[2], &saveptr1);
        if (token == NULL)
            break;
        printf("%d: %s\n", j, token);

        for (str2 = token; ; str2 = NULL) {
            subtoken = strtok_r(str2, argv[3], &saveptr2);
            if (subtoken == NULL)
                break;
            printf(" --> %s\n", subtoken);
        }
    }

    exit(EXIT_SUCCESS);
}
*/