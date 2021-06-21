# Compilador
CC=gcc

# Banderas
CFLAGS=-Wall -Wextra -std=gnu99 -ggdb

# Este es el ejecutable y sus dependencias serian los '.o'
minish:	linea2argv.o builtin_uid.o externo.o ejecutar.o builtin_pid.c builtin_gid.o builtin_cd.o builtin_env.o builtin_status.o builtin_dir.o builtin_history.o builtin_exit.o builtin_help.o utils.o builtin_huffman.o huffman_func.o heap_generic.o builtin_huffman_d.o wrappers.o IOutils.o


# Solo se agrega la dependencia al '.h'
minish.o: minish.h 
linea2argv.o: minish.h
builtin_uid.o: minish.h
externo.o: minish.h
ejecutar.o:	minish.h
builtin_status.o: minish.h
builtin_history.o: minish.h
builtin_exit.o: minish.h
builtin_help.o: minish.h
utils.o: minish.h

builtin_huffman.o: huffman.h huffman_func.h wrappers.h
huffman_func.o: huffman.h huffman_func.h wrappers.h
heap_generic.o: heap_generic.h
builtin_huffman_d.o: huffman.h wrappers.h huffman_func.h