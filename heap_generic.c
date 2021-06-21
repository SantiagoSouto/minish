/*
 * heap_generic.c
 *
 *
 * Gerardo Quincke - febrero 2020
 *
 * Funciones para construir un minheap o maxheap a partir de un array
 * La estructura heap se debe definir en forma externa
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
 */

#include "heap_generic.h"

void
swap_heap_elem(void *heapbase, size_t heaplen, size_t size, size_t i, size_t j)
/*
 * función que intercambia elementos i y j de un array
 * que comienza en la dirección heapbase con heaplen elementos de tamaño size
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */
{
    char *p, *q, temp;

    // procede solamente si i y j están en el rango correcto
    if (i != j && i < heaplen && j < heaplen) {
        p = (char *) heapbase + i * size;
        q = (char *) heapbase + j * size;
        while (size-- > 0) {
            temp = *p;
            *p++ = *q;
            *q++ = temp;
        }
    }
}

void
heap_bubbleup(void *heapbase, size_t heaplen, size_t size, size_t i,
                int (*compare)(const void *, const void *))
/*
 * función que ejecuta algoritmo estándar de inserción de UN elemento
 * se supone que el array del heap comienza en la dirección heapbase
 * con heaplen elementos de tamaño size y usa la función compare
 * para comparar elementos del array
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */
{
    size_t parent = (i - 1) / 2;   // división entera

    if (i >= heaplen)
        return;                 // fuera de rango

    while (i > 0 &&
            compare((char *)heapbase + size*i, (char *)heapbase + size*parent) ) {
        swap_heap_elem(heapbase, heaplen, size, i, parent);
        i = parent;
        parent = (i - 1) / 2;   // división entera
    }
}

void
heap_bubbledown(void *heapbase, size_t heaplen, size_t size, size_t i,
                int (*compare)(const void *, const void *))
/*
 * función que ejecuta algoritmo estándar de heapify o "bubbledown"
 * se supone que el array del heap comienza en la dirección heapbase
 * con heaplen elementos de tamaño size y usa la función compare
 * para comparar elementos del array
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */
{
    size_t left = 2*i + 1;
    size_t right = 2*i + 2;
    size_t minmax = i; // en minheap sería 'lowest' y en maxheap sería 'largest'

    if (left < heaplen &&
            compare((char *)heapbase + size*left, (char *)heapbase + size*minmax) ) {
        minmax = left;
    }
    if (right < heaplen &&
            compare((char *)heapbase + size*right, (char *)heapbase + size*minmax) ) {
        minmax = right;
    }

    if (minmax != i) {
        swap_heap_elem(heapbase, heaplen, size, i, minmax);
        heap_bubbledown(heapbase, heaplen, size, minmax, compare);
    }
}

void
build_heap(void *heapbase, size_t heaplen, size_t size,
                int (*compare)(const void *, const void *))
/*
 * función que ejecuta algoritmo estándar para crear un heap
 * se supone que el array del heap comienza en la dirección heapbase
 * con heaplen elementos de tamaño size y usa la función compare
 * para comparar elementos del array
 * El array empieza en índice 0 que es lo estándar en lenguaje C.
 *
 */
{
    int i;

    for (i=heaplen/2; i >= 0; i--) {
        heap_bubbledown(heapbase, heaplen, size, i, compare);
    }
}
