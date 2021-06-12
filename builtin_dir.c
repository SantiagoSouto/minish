#include "minish.h"

void _ls(char *route, char *needle) {
    DIR *d;
    struct dirent *dir;

    d = opendir(route);
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_ino != 0) {
            if (needle == NULL) {
                if (dir->d_type == DT_DIR) {
                    blue_bold();
                }
                printf("%s\t", dir->d_name);
                reset();
            } else if (strstr(dir->d_name, needle) != NULL) {
                if (dir->d_type == DT_DIR) {
                    blue_bold();
                }
                printf("%s\t", dir->d_name);
                reset();
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

    char *needle;

    switch (argc) {
        case 1:
            needle = NULL;
            break;
        case 2:
            needle = strdup(argv[1]);
            break;
        default:
            printf( "Demasiados argumentos\nUso: dir [texto]");
		    return 1;
    }

    _ls(".", needle);

    
    return EXIT_SUCCESS;
}