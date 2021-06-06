# Compilador
CC=gcc

# Banderas
CFLAGS=-Wall -Wextra -std=gnu99 -ggdb

# Este es el ejecutable y sus dependencias serian los '.o'
minish:	linea2argv.o builtin_uid.o externo.o ejecutar.o builtin_pid.c builtin_gid.o builtin_cd.o builtin_env.o builtin_status.o builtin_dir.o builtin_history.o io_utils.o stack_utils.o


# Solo se agrega la dependencia al '.h'
minish.o: minish.h 
linea2argv.o: minish.h
builtin_uid.o: minish.h
externo.o: minish.h
ejecutar.o:	minish.h
builtin_status.o: minish.h
builtin_history.o: minish.h
