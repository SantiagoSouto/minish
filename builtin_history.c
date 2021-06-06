#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include "minish.h"
#define DEFAULT 10

int builtin_history(int argc, char **argv) {
    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}
    extern struct stack *history;
    int n = DEFAULT;

    switch (argc) {
        case 1:
            break;
        case 2:
            if (*argv[1] != '-') {
                printf("Error de uso de history.\nUso: history [-n]\n");
                return 1;
            }
            n = atoi(argv[1]+1);
            break;
        default:
            printf("Solo un argumento es aceptado.\nUso: history [-n]\n");
            return 1;
    }

    if (history != NULL) {
        struct stack *temp = stack_create();
        for (struct stacknode *node = history->last; n > 0 && node != NULL; n--) {
            stack_push(temp, node->timestamp, node->word);
            node = node->prev;
        }
        stack_print(temp);
        stack_free(temp);
    }

    return EXIT_SUCCESS;
}