#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minish.h"

void my_reset() {
  printf("\033[0m");
}

// crea una lista vacía, retorna puntero a la misma
struct stack *stack_create() {
  struct stack *stack = (struct stack *) malloc(sizeof(struct stack));
  stack->count = 0;
  stack->last = NULL;
  return stack;
}

// inserta una palabra al final de la lista l, retorna el puntero a la lista
// si la lista es NULL, crea una nueva
struct stack *stack_push(struct stack *s, char *timestamp, char *word) {
  struct stacknode *node = (struct stacknode *) malloc(sizeof(struct stacknode));
  node->timestamp = strdup(timestamp);
  node->word = strdup(word);

  if (s->count == 0) {
    node->prev = NULL;
  } else {
    node->prev = s->last;
  }

  s->last = node;
  (s->count)++;
  
  return s;
}

void stack_free(struct stack *s) {
  struct stacknode *node = s->last;
  for (; node->prev != NULL; node = node->prev) {
    free(node->timestamp);
    free(node->word);
  }
  free(s);
}

void stack_print(struct stack *s) {
  for (struct stacknode *n = s->last; n != NULL; n = n->prev) {
    printf("%s:  %s%s", n->timestamp, "\033[0;34m", n->word);
  }
  my_reset();
}