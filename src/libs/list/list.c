#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List create_list(void) {
  return NULL;
}

bool is_empty(List list) {
  return list == NULL || list->length == 0;
}

List push_back_list(List list, void *x, ListElementType elementType) {
  Node *element;
  element = malloc(sizeof(*element));

  if (element == NULL) {
    fprintf(stderr, "Error: dynamic allocation problem");
    exit(EXIT_FAILURE);
  }

  element->value = x;
  element->previous = NULL;
  element->next = NULL;

  if (is_empty(list)) {
    list = malloc(sizeof(*list));

    if (list == NULL) {
      fprintf(stderr, "Error: dynamic allocation problem");
      exit(EXIT_FAILURE);
    }

    list->elementType = elementType;
    list->length = 0;
    list->first = element;
    list->last = element;

  } else {
    if (elementType != list->elementType) {
      fprintf(stderr, "Error: the type is different");
      exit(EXIT_FAILURE);
    }

    list->last->next = element;
    element->previous = list->last;
    list->last = element;
  }

  list->length += 1;

  return list;
}

List pop_back_list(List list) {
  if (is_empty(list)) {
    printf("Nothing to delete, the list is empty");
    return create_list();
  }

  if (list->first == list->last) {
    free(list);
    list = NULL;
    return create_list();
  }

  Node *temp = list->last;

  list->last = list->last->previous;
  list->last->next = NULL;

  temp->next = NULL;
  temp->previous = NULL;

  free(temp);
  temp = NULL;

  list->length--;
  return list;
}

List clear_list(List list) {
  while (!is_empty(list)) {
    list = pop_back_list(list);
  }

  return create_list();
}