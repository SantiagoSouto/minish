#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <error.h>
/*
 * huffman.h
 * Estructuras requeridas para resolver compresión/descompresión Huffman,
 * de acuerdo al algoritmo de Wikipedia.
 *
 * El archivo comprimido tendrá este formato:
 * - un cabezal que identifica este archivo y contiene datos del contenido posterior
 *   (8 bytes)
 * - un array de elementos, cada uno de los cuales identifica un símbolo y su bitmask
 *   (8 bytes por símbolo)
 * - un string de bits que representan el contenido del archivo original,
 *   transformado según el algoritmo de compresión.
 *   (resto del contenido del archivo)
 * 
 */

#define MAXSYMBOL 256               // Valores 0 a 255 (8 bits)
#define MYMAGICNBR 0x5147           // mi número mágico para archivos ("GQ")
#define MAXFILELEN (1ul << 24)      // tamaño máximo de archivos (24 bits)

// CABEZAL DEL ARCHIVO COMPRIMIDO
typedef struct compr_header {       // 8 bytes: cabezal de archivo comprimido
    uint16_t    magic_nbr;          // número mágico (2)
    uint8_t     sym_arraylen;       // largo del array de los Symcode (1)
    uint8_t     sym_arraysize;      // tamaño de cada elemento del array anterior (1)
    uint32_t    filelen;            // largo del archivo original en bytes (4)
} Compr_header;

                                    // optimizado para aprovechar al máximo 32 bits
#define BITSFORMASK 27              // largo máximo de la máscara: 27 bits
#define MAXMASK (1ul << BITSFORMASK) // para controlar error por overflow

// REPRESENTACIÓN DE 1 SIMBOLO
typedef struct symcode {            // 8 bytes para cada símbolo existente en la entrada
    uint64_t    symbol: 8,          // 8 bits para el símbolo (byte)
                count: 24,          // 24 bits para la cantidad de ocurrencias (16Mega)
                mask: BITSFORMASK,      // definido más arriba como 27
                masklen: 32 - BITSFORMASK;  // 5 bits para representar el largo
} Symcode;

/*
 * La estructura de un nodo del árbol, que tendrá dos formas de acceso:
 * Una es un array accedido como un heap.
 * La otra es como un árbol, para lo cual están los punteros a sus hijos.
 *
 */
typedef struct treenode {
    struct symcode *code;       // si es hoja, todos los datos del símbolo
    struct treenode *children[2];   // Si es interno, punteros a hijos (0=izq, 1=der)
} Treenode;

/*
 * La estructura de un heap para almacenar los nodos del árbol
 *
 */
typedef struct heap {
    int capacity;           // la capacidad máxima de elementos de este heap
    int used;               // la cantidad de elementos usados
    Treenode **nodearray;   // array mallocado, símil nodearray[capacity]
} Heap;

