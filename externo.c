#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int externo(int argc, char **argv) {

    pid_t child_process;
    if (argc > 0) {
        child_process = fork();
        int wstatus;
        switch (child_process) {
        case -1:
            error(1, errno, "Error al duplicar proceso (fork)\n");
            break;
        case 0:
            execvp(*argv, argv);
            error(2, errno, "Comando desconocido\n");
            break;
        default:
            while (wait(&wstatus) != child_process){
                ;
            }
            break;
        }
    } else {
        error(3, errno, "No se pasaron argumentos para ejecutar");
    }
    return 0;

}
