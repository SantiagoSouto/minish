#include "minish.h"
#define DEFAULT 10

int builtin_history(int argc, char **argv) {
    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}
    extern struct list *history;
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
    
    struct list *temp = list_create();

    if (history != NULL) {
        int left = n - (history->count);

        for (struct listnode *node = history->last; n > 0 && node != NULL; n--, node = node->prev) {
            list_push(temp, node->cmd);
        }
        if (left >= 0) {
            get_history(temp, left);
        }
    } else {
        get_history(temp, n);
    }
    list_print(temp);
    list_free(temp);

    return EXIT_SUCCESS;
}