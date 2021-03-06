#include "minish.h"


/*
*******************************************
************* COLORING UTILS **************
*******************************************
*/
///Finalmente no fueron usadas en la primer version
void blue_bold() {
  printf("\033[1;34m");
}

void reset() {
  printf("\033[0m");
}


/*
*******************************************
*************** STACK UTILS ***************
*******************************************
*/


// crea una lista vacía, retorna puntero a la misma
struct list *list_create() {
  struct list *list = (struct list *) malloc(sizeof(struct list));
  list->count = 0;
  list->first = NULL;
  list->last = NULL;
  return list;
}

// inserta una palabra al final de la lista l, retorna el puntero a la lista
struct list *list_push(struct list *l, char *cmd) {
  struct listnode *node = (struct listnode *) malloc(sizeof(struct listnode));
  node->cmd = strdup(cmd);
  node->next = NULL;

  if (l == NULL) {
	  l = list_create();
  }
  
  if (l->count == 0) {
	  node->prev = NULL;
	  l->first = node;
	  l->last = node;
	  (l->count)++;
	  return l;
  }

  node->prev = l->last;
  l->last->next = node;
  l->last = node;
  (l->count)++;
  
  return l;
}

// Elimina la lista con sus respectivos free
void list_free(struct list *l) {
  struct listnode *node = l->first;
  for (; node != NULL; node = node->next) {
    free(node->cmd);
  }
  free(l);
}

// Imprime la lista
void list_print(struct list *l) {
  for (struct listnode *n = l->last; n != NULL; n = n->prev) {
    printf("%s", n->cmd);
  }
  reset();
}



/*
*******************************************
************** IN/OUT UTILS ***************
*******************************************
*/

//Funciones encargadas de las redirecciones de entrada salida

int fd_out;
fpos_t pos_out;


int fd_in;
fpos_t pos_in;

//Vuelve la salida a la original (consola donde se ejecuto minish)
void reset_out() {
	fflush(stdout);
	dup2(fd_out, fileno(stdout));
	close(fd_out);
	clearerr(stdout);
	fsetpos(stdout, &pos_out);
	//Importante setear lel stdout sin buffer para que se escriba todo en tiempo real
	setvbuf(stdout, NULL, _IONBF, 0);
	reset_out_needed = 0;
}

//Vuelve la entrada a la original (consola donde se ejecuto minish)
void reset_in() {
	fflush(stdin);
	dup2(fd_in, fileno(stdin));
	close(fd_in);
	clearerr(stdin);
	fsetpos(stdin, &pos_in);
	reset_in_needed = 0;
}

//Se encarga de resolver la necesidad de resetear outpu/input
void io_reset() {
	if( reset_out_needed ){
		reset_out();

	}
	if( reset_in_needed ){
		reset_in();
	}
}


//Se encarga de camviar direccion de salida
int set_out(char *fname, char *tp) {
	FILE *fp;
	//Se abre el archivo de la nueva salida para saegurarse que no hay errores. Se maneja el error o se cierra y se continua
	//Ineficiente pero mas seguro 
	if( (fp=fopen(fname, tp)) == NULL ){
		return errno;
	} else{
		fclose(fp);
	}

	//Se escribe lo que estaba en el buffer de escritura. Se duplica el file descriptor y se remplaza el stdout por el nuevo. Se cierra stdout
	fflush(stdout);
	fgetpos(stdout, &pos_out);
	fd_out = dup(fileno(stdout));
	if( freopen(fname, tp, stdout) == NULL ){
		return errno;
	}
	reset_out_needed = 1;
	return 0;
}


//Se encarga de camviar direccion de salida
int set_in(char *fname, char *tp) {

	//Se abre el archivo de la nueva entrada para saegurarse que no hay errores. Se maneja el error o se cierra y se continua
	//Ineficiente pero mas seguro 
	FILE *fp;
	if( (fp=fopen(fname, tp)) == NULL ){
		return errno;
	} else{
		fclose(fp);
	}

	//Se escribe lo que estaba en el buffer de escritura (innecesario en este caso). Se duplica el file descriptor y se remplaza el stdin por el nuevo. Se cierra stdout
	fflush(stdin);
	fgetpos(stdin, &pos_in);
	fd_in = dup(fileno(stdin));
	if( freopen(fname, tp, stdin) == NULL ){
		return errno;
	}
	reset_in_needed = 1;
	return 0;
}

//Funcion que atiende solicitudes de redireccion de entrada salida a un archivo especifico
int io_set( char *fname) {
	char *tp;
	char wr[] = "w", ap[] = "a";

	//Se busca cual es la redireccionn deseada
	if( *fname == '>' ){

		if( *(fname+1) == '>' ) {
			tp = ap;
			fname = fname + 2;
		} else{
			tp = wr;
			fname = fname + 1;
		}
		return set_out(fname, tp);
		
	} else if( *fname++  == '<' ){
		return set_in(fname, "r");
	}


	return EXIT_SUCCESS;

}


/*
*******************************************
************** HISTORY UTILS **************
*******************************************
*/

// Genera el timestamp para el history con sus respectivos colores de impresión
char *get_timestamp() {
    
	char *timestamp = (char *)malloc(sizeof(char));
	time_t *current_time = malloc(sizeof(time_t));
	time(current_time);
	if (*current_time == ((time_t)-1))
    {
        fprintf(stderr, "Failure to obtain the current time.\n");
        return NULL;
    }
	struct tm *tm;
	tm = localtime(current_time);
    
    sprintf(timestamp,"%s%04d-%02d-%02d %s%02d:%02d:%02d", "\033[0;32m", tm->tm_year+1900, tm->tm_mon, 
    tm->tm_mday, "\033[0m", tm->tm_hour, tm->tm_min, tm->tm_sec);

    if (timestamp == NULL)
    {
        printf("Error al convertir el tiempo a formato timestamp.\n");
        return NULL;
    }
    return timestamp;
}

// Guarda el comando line en la lista de history
int save_history(char *line) {
	char *timestamp = get_timestamp();
	if (timestamp == NULL) {
		return 1;
	}

	if (history == NULL) {
		history = list_create();
	}

	char *cmd = malloc(sizeof(char)*MAXWORDS);
	snprintf(cmd, MAXWORDS, "%s:  %s%s", timestamp, "\033[0;34m", line);

	history = list_push(history, cmd);
	free(timestamp);
	free(cmd);
	return 0;

}

// Graba en el archivo .minish_history la lista actual de comandos ejecutados
int write_history() {
    char *pathname = malloc(sizeof(char)*MAXWORDS);
    snprintf(pathname, MAXWORDS, "/home/%s/.minish_history", getenv("USER"));

    FILE *hist = fopen(pathname, "r+");

    if (hist == NULL) {
        hist = fopen(pathname, "w");             
    }

    for (struct listnode *node = history->last; node != NULL; node = node->prev) {
        fprintf(hist, "%s", node->cmd);
    }

    fclose(hist);
    list_free(history);
	free(pathname);
    return 0;
}

// Lee las primeras n lineas del archivo .minish_history
int get_history(struct list *l, int n) {
	char *pathname = malloc(sizeof(char)*MAXWORDS);
    snprintf(pathname, MAXWORDS, "/home/%s/.minish_history", getenv("USER"));

    FILE *hist = fopen(pathname, "r");

	if (hist == NULL) {   
        return 0;             
    }

	char line[MAXLINE];

	while (fgets(line, MAXLINE, hist) != NULL && n-- > 0) {
		l = list_push(l, line);
	}
	fclose(hist);
	free(pathname);
	return 0;
}


/*
*******************************************
*************** SIGNAL UTILS **************
*******************************************
*/

// Función que captura el Ctrl+C
void interrupt_ctrl_c() {
	fprintf(stderr, "Linea cancelada.\nVuelva a escribir el comando deseado: > ");
}

// Función al terminar la ejecución del minish
void exit_status() {
	fprintf(stderr, "Exiting...\n");
	builtin_status(1, NULL);
}
