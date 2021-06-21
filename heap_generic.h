/*
 * heap_generic.h
 *
 * Gerardo Quincke - febrero 2020
 *
 * Declaraciones de las funciones definidas en heap_generic.c
 *
 * El programador debe incluir una función de comparación con esta definición
 * int compare(const void *p, const void *q)
 *
 * Estas funciones armarán el heap usando la función compare externa.
 * Por ejemplo:
 *
    int
    heap_min_compare(const void *p, const void *q)
    {
        // compara POR MENOR dos estructuras heap *p y *q, de acuerdo a su campo prio
        const struct heap *hp = p, *hq = q;
        return hp->prio < hq->prio;
    }

    int
    heap_max_compare(const void *p, const void *q)
    {
        // compara POR MAYOR dos estructuras heap *p y *q, de acuerdo a su campo prio
        const struct heap *hp = p, *hq = q;
        return hp->prio > hq->prio;
    }
 *
 *
 */
#include <stddef.h>

extern void swap_heap_elem(void *heapbase, size_t heaplen, size_t size, size_t i, size_t j);
/*
 * función que intercambia elementos i y j de un array
 * que comienza en la dirección heapbase con heaplen elementos de tamaño size
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */


extern void heap_bubbleup(void *heapbase, size_t heaplen, size_t size, size_t i,
                int (*compare)(const void *, const void *));
/*
 * función que ejecuta algoritmo estándar de inserción de UN elemento
 * se supone que el array del heap comienza en la dirección heapbase
 * con heaplen elementos de tamaño size y usa la función compare
 * para comparar elementos del array
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */


extern void heap_bubbledown(void *heapbase, size_t heaplen, size_t size, size_t i,
                int (*compare)(const void *, const void *));
/*
 * función que ejecuta algoritmo estándar de heapify o "bubbledown"
 * se supone que el array del heap comienza en la dirección heapbase
 * con heaplen elementos de tamaño size y usa la función compare
 * para comparar elementos del array
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */


extern void build_heap(void *heapbase, size_t heaplen, size_t size,
                int (*compare)(const void *, const void *));
/*
 * función que ejecuta algoritmo estándar para crear un heap
 * se supone que el array del heap comienza en la dirección heapbase
 * con heaplen elementos de tamaño size y usa la función compare
 * para comparar elementos del array
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */

