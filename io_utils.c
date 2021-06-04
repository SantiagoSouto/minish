#include "minish.h"
#include <stdio.h>

int fd_out;
fpos_t pos_out;


int fd_in;
fpos_t pos_in;

void 
reset_out()
{
	fflush(stdout);
	dup2(fd_out, fileno(stdout));
	close(fd_out);
	clearerr(stdout);
	fsetpos(stdout, &pos_out);
	setvbuf(stdout, NULL, _IONBF, 0);
	reset_out_needed = 0;
}

void 
reset_in()
{
	fflush(stdin);
	dup2(fd_in, fileno(stdin));
	close(fd_in);
	clearerr(stdin);
	fsetpos(stdin, &pos_in);
	reset_in_needed = 0;
}


void
io_reset()
{
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



int
set_out(char *fname, char *tp)
{
	fflush(stdout);
	fgetpos(stdout, &pos_out);
	fd_out = dup(fileno(stdout));
	if( freopen(fname, tp, stdout) == NULL ){
		return errno;
	}
	reset_out_needed = 1;
	return 0;
}


int
set_in(char *fname, char *tp)
{
	fflush(stdin);
	fgetpos(stdin, &pos_in);
	fd_in = dup(fileno(stdin));
	if( freopen(fname, tp, stdin) == NULL ){
		return errno;
	}
	reset_in_needed = 1;
	return 0;
}

int
io_set( char *fname)
{
	char *tp;
	char wr[] = "w", ap[] = "a";
	FILE *fp;


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
