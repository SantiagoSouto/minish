#include "minish.h"
#define DEFAULT 10

int builtin_history(int argc, char **argv) 
{
	/*
     * 
     * Función que imprime el historial de comandos ejecutados
     * por el usuario. Dependiendo de la cantidad de comandos 
     * pedidos (por argumento con la flag "-" adelante) se imprime
     * dicha cantidad, si no, por defecto se imprimen 10.
     * 
    */

    // Verifica que se tenga algún argumento
    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}
    // Lista con comandos realizados durante la ejecución del programa
    extern struct list *history;
    int n = DEFAULT;

    // Según la cantidad de argumentos, según la cantidad de comandos que se imprimen
    switch (argc) {
        // Se mantiene por defecto los últimos 10 comandos
        case 1:
            break;
        case 2:
            // Solo se acepta un segundo argumento, si es la flag con cantidad de comandos (debe tener un "-" adelante)
            if (*argv[1] != '-') {
                printf("Error de uso de history.\nUso: history [-n]\n");
                return 1;
            }
            // Convierte la cantidad deseada en un entero
            n = atoi(argv[1]+1);
            break;
        default:
            printf("Solo un argumento es aceptado.\nUso: history [-n]\n");
            return 1;
    }
    
    // lista temporal para guardar los n comandos deseados y luego imprimirlos
    struct list *temp = list_create();

    // Revisa si existen comandos ejecutados en el programa, si no existen, directamente abre el archivo
    // donde se guarda el histórico de comandos de ese usuario
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