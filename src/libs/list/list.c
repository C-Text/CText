#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List create_list(void) {
  return NULL;
}

bool is_empty(List list) {
  if (list == NULL)
    return true;

  if (list->length == 0)
    return true;

  return false;
}

unsigned long get_length(List list) {
  if (is_empty(list))
    return 0;

  return list->length;
}

Node *get_first_element(List list) {
  if (is_empty(list)) {
    fprintf(stderr, "Error: Cannot get first element on empty list");
    exit(EXIT_FAILURE);
  }

  return list->first;
}

Node *get_last_element(List list) {
  if (is_empty(list)) {
    fprintf(stderr, "Error: Cannot get last element on empty list");
    exit(EXIT_FAILURE);
  }

  return list->last;
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

List push_front_list(List list, void *x, ListElementType elementType) {
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

    list->first->previous = element;
    element->next = list->first;
    list->first = element;
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

List pop_front_list(List list) {
  if (is_empty(list)) {
    printf("Nothing to delete, the list is empty");
    return create_list();
  }

  if (list->first == list->last) {
    free(list);
    list = NULL;
    return create_list();
  }

  Node *temp = list->first;

  list->first = list->first->next;
  list->first->previous = NULL;

  temp->next = NULL;
  temp->previous = NULL;

  free(temp);
  temp = NULL;

  list->length--;
  return list;
}

Node *get_element_by_index(List list, int i) {
  if ((unsigned long) i >= list->length) {
    fprintf(stderr, "Error: the i is out the range of the ");
    exit(EXIT_FAILURE);
  }

  Node *node = list->first;

  while (i > 0) {
    node = node->next;
    i--;
  }

  return node;

}

List clear_list(List list) {
  while (!is_empty(list)) {
    list = pop_back_list(list);
  }

  return create_list();
}

void for_each_in(List list, void (*f)(Node *, size_t, void *), void *args) {
  Node *current_node = list->first;
  for (size_t i = 0; i < list->length; i++) {
    f(current_node, i, args);
    current_node = current_node->next;
  }
}