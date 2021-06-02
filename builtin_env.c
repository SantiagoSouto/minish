#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

int builtin_getenv (int argc, char **argv) {
    (argc < 1) ? error(1, errno, "No hay argumentos suficientes\n");
    
    switch (argc) {
        case 1:
            for (; *__environ != NULL; __environ++) {
                printf("%s\n", *__environ);
            }
            break;
        default:
            char *env = malloc(sizeof(char));
            for (++argv; *argv != NULL; argv++) {
                env = getenv(*argv);
                if (env == NULL) {
                    fprintf(stderr, "env %s: No se encuentra definida.\n", *argv);
                } else {
                    printf("%s\n", env);
                }
            }
            free(env);
    }
    exit(EXIT_SUCCESS);
}

int builtin_setenv (int argc, char ** argv) {
    (argc != 3) ? error(1, errno, "Cantidad de argumentos no coincide.\nUso: setenv [nombre] [valor]\n");

    int status = setenv(*(++argv), *(++argv), 1);

    if (!status) {
        error(2, errno, "Error agregando variable de entorno.\nUso: setenv [nombre] [valor]");
    }

    
    exit(EXIT_SUCCESS);
}

int builtin_unsetenv (int argc, char ** argv) {
    (argc < 1) ? error(1, errno, "No hay argumentos suficientes\n");

    switch (argc) {
        case 1:
            error(2, errno, "No se especifican variables a eliminar.\nUso: unsetenv [var..]\n");
            break;
        default:
            int status;
            for (++argv; *argv != NULL; argv++) {
                status = unsetenv(*argv);
                if (!status) {
                    fprintf(stderr, "Error al eliminar variable %s.\n", *argv);
                }
            }
    }
    exit(EXIT_SUCCESS);
}