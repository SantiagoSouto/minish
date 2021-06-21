#include "minish.h"

int builtin_dir (int argc, char **argv) 
{
    /*
     * 
     * Función que muestra el directorio actual, diferenciando entre
     * archivos y directorios. Además, tiene la opción de recibir un 
     * argumento con parte del nombre de algún archivo en el directorio
     * el cual se analiza como "aguja en pajar" en cada archivo o 
     * directorio encontrado.
     * 
    */
    // Abre la ruta, y muestra aquellos archivos que contengan needle, si no es NULL
    void _ls(char *route, char *needle);

    // Verifica que se tenga algún argumento
    if( argc < 1 ){
		printf( "No hay argumentos suficientes\n");
		return 1;
	}

    char *needle;

    // Asigna, si es necesario, el texto a buscar en needle
    switch (argc) {
        case 1:
            // Se debe mostrar todo en el directorio
            needle = NULL;
            break;
        case 2:
            // Se debe mostrar solo aquellos que contengan a needle
            needle = strdup(argv[1]);
            break;
        default:
            printf( "Demasiados argumentos\nUso: dir [texto]");
		    return 1;
    }

    // Llamamos a la función para el directorio actual
    _ls(".", needle);
    
    return EXIT_SUCCESS;
}


void _ls(char *route, char *needle) 
{
    /* 
     *
     * Función que abre el directorio de route e itera por su contenido,
     * donde si needle no es NULL, se imprime aquél contenido que contenga
     * a needle, si no, muestra todo el contenido
     * 
    */
    // Estructura para abrir el directorio de route
    DIR *d;
    // Estructura para usar el contenido del directorio abierto
    struct dirent *dir;

    // Se abre el directorio
    d = opendir(route);
    // Se mantendrá en el loop, leyendo todo el contenido, hasta que no haya más que leer
    while ((dir = readdir(d)) != NULL) {
        // Verifica que el archivo o directorio abierto sea válido
        if (dir->d_ino != 0) {
            // Si es un directorio, imprimir en color azul
            if (dir->d_type == DT_DIR) {
                blue_bold();
            }
            // Verificar needle, y evaluar si no es NULL
            if (needle == NULL) {
                printf("%s\t", dir->d_name);
            } else if (strstr(dir->d_name, needle) != NULL) {
                printf("%s\t", dir->d_name);
            }
            // Volver a la impresión con color normal
            reset();
        }
    }
    // Se cierra el directorio
    closedir(d);
    printf("\n");
}