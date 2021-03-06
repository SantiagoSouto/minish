#define MAXLINE 1024        // tamaño máximo de la línea de entrada
#define MAXCWD 1024         // tamaño máximo para alojar el pathname completo del directorio corriente
#define MAXWORDS 256        // cantidad máxima de palabras en la línea
#define HISTORY_FILE	".minish_history"   // nombre del archivo que almacena historia de comandos
#define MAXARG 100
#define MAXGROUPS 100
#define ENDSTR "FIN\n"

#define HELP_CD      "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR     "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT    "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP    "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid|huffman|huffman-d]"
#define HELP_HISTORY "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV  "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID     "pid - muestra Process Id del minish"
#define HELP_UNSETENV  "unsetenv var [var] - elimina el valor de variable de ambiente"
#define HELP_SETENV  "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS  "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID     "uid - muestra nombre y número de usuario dueño del minish"
#define HELP_GID     "gid - muestra el grupo principal y los grupos secundarios del usuario dueño del minish"
#define HELP_HUFFMAN "huffman [file] - comprime un archivo con el algoritmo de Huffman"
#define HELP_HUFFMAN_D "huffman-d [file] - descomprime un archivo comprimido por el algoritmo de Huffman"


#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <error.h>
#include <errno.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <grp.h>

extern int minish_run;


// Variables
extern int globalstatret;	// guarda status del ultimo comando - deberá definirse en el main
extern FILE *base_stdin;
extern FILE *base_stdout;
// Funciones
extern int builtin_exit (int argc, char **argv);
extern int builtin_help (int argc, char **argv);
extern int builtin_history (int argc, char **argv);
extern int builtin_status (int argc, char **argv);
extern int builtin_cd (int argc, char **argv);
extern int builtin_dir (int argc, char **argv);
extern int builtin_getenv (int argc, char **argv);
extern int builtin_gid (int argc, char **argv);
extern int builtin_setenv (int argc, char **argv);
extern int builtin_pid (int argc, char **argv);
extern int builtin_uid (int argc, char **argv);
extern int builtin_unsetenv (int argc, char **argv);
extern int ejecutar (int argc, char **argv);
extern int externo (int argc, char **argv);
extern int linea2argv(char *linea, int argc, char **argv);

extern int builtin_huffman (int argc, char **argv);
extern int builtin_huffman_d (int argc, char **argv);

struct builtin_struct {         // struct con información de los builtins
    char *cmd;                  // nombre del comando builtin
    int (*func) (int, char **); // la función que lo ejecuta
    char *help_txt;             // el texto de ayuda
};

struct list {
    int count;
    struct listnode *first;
    struct listnode *last;
};

struct listnode {
    char *cmd;
    struct listnode *next;
    struct listnode *prev;
};


extern char *getcwd (char *__buf, size_t __size) __THROW __wur;
extern int chdir (const char *__path) __THROW __nonnull ((1)) __wur;

extern int reset_in_needed;
extern int reset_out_needed;

/*
*******************************************
************* UTIL FUNCTIONS **************
*******************************************
*/

// Coloring utils
extern void blue_bold();
extern void reset();

// Stack utils
extern struct list *list_create();
extern struct list *list_push(struct list *l, char *cmd);
extern void list_free(struct list *l);
extern void list_print(struct list *l);

// In/Out utils
extern void reset_out();
extern void reset_in();
extern int io_set(char *fname);
extern void io_reset();
extern int set_in(char *fname, char *tp);
extern int set_out(char *fname, char *tp);

// History utils
extern char *get_timestamp();
extern int save_history(char *line);
extern int write_history();
extern int get_history(struct list *l, int n);

// Signal utils
extern void interrupt_ctrl_c();
extern void exit_status();





extern struct list *history;
extern struct listnode *use_cmd;
extern struct builtin_struct builtin_arr[];
extern struct builtin_struct *builtin_lookup(char *cmd);
/*
    builtin_arr es una lista de los builtins, que se recorrerá en forma lineal.
    Podría usarse una estructura que mejorara la velocidad de búsqueda, pero
    en este ejercicio una lista que se recorre en forma lineal es suficiente.
    Deberá definirse e inicializarse como variable global, de esta manera:
    struct builtin_struct builtin_arr[] = {
        { "cd", builtin_cd, HELP_CD },
        .... etc. etc.
        { "uid", builtin_uid, HELP_UID },
        { NULL, NULL, NULL }
    };
    La definición no puede hacerse en este archivo minish.h porque está pensado
    para ser incluido en todos los fuentes y no se puede definir el mismo array en
    diferentes fuentes de un mismo programa.
*/

/*
    La siguiente lista de constantes de texto puede adaptarse/mejorarse, se pone como ejemplo.
    Lo lógico sería que estuvieran definidas en el mismo fuente que define el array builtin_arr
    en lugar de estar en este archivo .h.

*/

