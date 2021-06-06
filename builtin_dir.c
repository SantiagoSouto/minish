#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

void _ls(char *route, int opt_l, int opt_a) {
    DIR *d;
    struct dirent *dir;

    d = opendir(route);
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_ino != 0) {
            if (opt_a || dir->d_name[0] != '.') {
                if (dir->d_type == DT_DIR) {
                    blue_bold();
                }
                printf("%s\t", dir->d_name);
                reset();
                if (opt_l) {
                    printf("\n");
                }
            }
        }
    }
    closedir(d);
    printf("\n");
}

int builtin_dir (int argc, char **argv) {
    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}

    char **route = malloc(sizeof(char));
    int routes;
    int opt_a, opt_l;
    opt_a = opt_l = 0;

    for (int i = routes = 0; argv[i] != NULL; i++) {
        if (*argv[i] == '-') {
            if (strcmp(argv[i], "-l") == 0) {
                opt_l = 1;
            } else if (strcmp(argv[i], "-a") == 0) {
                opt_a = 1;
            } else if (strcmp(argv[i], "-la") == 0) {
                opt_a = opt_l = 1;
            } else {
                printf("Bandera no reconocida. Banderas habilitadas: \n-l \n-a \n-la");
                return 1;
            }
        } else if (strcmp(argv[i], "dir") != 0) {
            route[routes++] = strdup(argv[i]);
        }
    }
    route[routes++] = NULL;

    if (routes == 1) {
        _ls(".", opt_l, opt_a);
    } else {    
        for(; *route != NULL; route++) {
            if (routes > 2) {
                printf("\n%s:\n\n", *route);
            }
            _ls(*route, opt_l, opt_a);
        }
    }

    
    return EXIT_SUCCESS;
}