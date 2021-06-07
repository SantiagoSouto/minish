#include "minish.h"


/*
*******************************************
************* COLORING UTILS **************
*******************************************
*/

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


// crea un stack vacío, retorna puntero al mismo
struct stack *stack_create() {
  struct stack *stack = (struct stack *) malloc(sizeof(struct stack));
  stack->count = 0;
  stack->last = NULL;
  return stack;
}

// inserta una palabra al final del stack s, retorna el puntero al stack
struct stack *stack_push(struct stack *s, char *cmd) {
  struct stacknode *node = (struct stacknode *) malloc(sizeof(struct stacknode));
  node->cmd = strdup(cmd);

  if (s == NULL) {
	  s = stack_create();
  }

  node->prev = s->last;
  s->last = node;
  (s->count)++;
  
  return s;
}

void stack_free(struct stack *s) {
  struct stacknode *node = s->last;
  for (; node->prev != NULL; node = node->prev) {
    free(node->cmd);
  }
  free(s);
}

void stack_print(struct stack *s) {
  for (struct stacknode *n = s->last; n != NULL; n = n->prev) {
    printf("%s", n->cmd);
  }
  reset();
}



/*
*******************************************
************** IN/OUT UTILS ***************
*******************************************
*/


int fd_out;
fpos_t pos_out;


int fd_in;
fpos_t pos_in;

void reset_out() {
	fflush(stdout);
	dup2(fd_out, fileno(stdout));
	close(fd_out);
	clearerr(stdout);
	fsetpos(stdout, &pos_out);
	setvbuf(stdout, NULL, _IONBF, 0);
	reset_out_needed = 0;
}

void reset_in() {
	fflush(stdin);
	dup2(fd_in, fileno(stdin));
	close(fd_in);
	clearerr(stdin);
	fsetpos(stdin, &pos_in);
	reset_in_needed = 0;
}


void io_reset() {
	/*	FILE *cp;
		if( base_stdout != stdout ){
		cp = stdout;	
		fclose(cp);
		stdout = base_stdout;
		}
		if( base_stdin != stdin ){
		cp = stdin;	
		fclose(cp);
		stdin = base_stdin;
		}
		*/

	//	freopen("/dev/stdout", "w", stdout);
	//	freopen("dev/stdin", "r", stdin);


	if( reset_out_needed ){
		reset_out();

	}

	if( reset_in_needed ){
		reset_in();
	}
}



int set_out(char *fname, char *tp) {
	fflush(stdout);
	fgetpos(stdout, &pos_out);
	fd_out = dup(fileno(stdout));
	if( freopen(fname, tp, stdout) == NULL ){
		return errno;
	}
	reset_out_needed = 1;
	return 0;
}


int set_in(char *fname, char *tp) {
	fflush(stdin);
	fgetpos(stdin, &pos_in);
	fd_in = dup(fileno(stdin));
	if( freopen(fname, tp, stdin) == NULL ){
		return errno;
	}
	reset_in_needed = 1;
	return 0;
}

int io_set( char *fname) {
	char *tp;
	char wr[] = "w", ap[] = "a";
	// FILE *fp;


	if( *fname == '>' ){

		if( *(fname+1) == '>' ) {
			tp = ap;
			fname = fname + 2;
		} else{
			tp = wr;
			fname = fname + 1;
		}

		//	if( (fp = freopen(fname, tp, stdout)) == NULL ){
		//		return errno;
		//	}
		//stdout = fp;
		//
		//return 0;
		return set_out(fname, tp);
		
	} else if( *fname++  == '<' ){

		//	if( (fp = freopen(fname, "r", stdin)) == NULL ){
		//		return errno;
		//	}
		//stdin = fp;
		//	return 0;
		return set_in(fname, "r");
	}


	return EXIT_SUCCESS;

}


/*
   int
   set_output(char *fname)
   {
   FILE *fp;
   if( (fp = fopen(fname, "w")) == NULL ){
   return errno;
   }

   stdout = fp;

   return EXIT_SUCCESS;
   }
   */



/*
*******************************************
************** HISTORY UTILS **************
*******************************************
*/


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

int save_history(char *line) {
	char *timestamp = get_timestamp();
	if (timestamp == NULL) {
		return 1;
	}

	if (history == NULL) {
		history = stack_create();
	}

	char *cmd = malloc(sizeof(char)*MAXWORDS);
	snprintf(cmd, MAXWORDS, "%s:  %s%s", timestamp, "\033[0;34m", line);

	history = stack_push(history, cmd);
	free(timestamp);
	free(cmd);
	return 0;

}

int write_history() {
    char *pathname = malloc(sizeof(char)*MAXWORDS);
    snprintf(pathname, MAXWORDS, "/home/%s/.minish_history", getenv("USER"));

    FILE *hist = fopen(pathname, "w");

    if (hist == NULL) {
        printf("Error abriendo .minish_history");   
        return 1;             
    }

	struct stack *temp = stack_create();
    for (struct stacknode *node = history->last; node != NULL; node = node->prev) {
        temp = stack_push(temp, node->cmd);
    }

    for (struct stacknode *n = temp->last; n != NULL; n = n->prev) {
        fprintf(hist, "%s", n->cmd);
    }

    fclose(hist);
	stack_free(temp);
    stack_free(history);
	free(pathname);
    return 0;
}

int get_history() {
	char *pathname = malloc(sizeof(char)*MAXWORDS);
    snprintf(pathname, MAXWORDS, "/home/%s/.minish_history", getenv("USER"));

    FILE *hist = fopen(pathname, "r");

	if (hist == NULL) {   
        return 0;             
    }

	char line[MAXLINE];

	while (fgets(line, MAXLINE, hist) != NULL) {
		history = stack_push(history, line);
	}
	fclose(hist);
	free(pathname);
	return 0;
}


/*
*******************************************
*************** ARROWS UTILS **************
*******************************************
*/

