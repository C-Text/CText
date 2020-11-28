#ifndef CTEXT_LIST_H
#define CTEXT_LIST_H

#include <stdbool.h>

// ================================
// Type definition
// ================================

typedef enum {
  NeuronType,
  LinkType,
  LayerType
} ListElementType;

/**
 * Node
 * Definition of a node of the list
 */
typedef struct Node {
  void *value;
  struct Node *previous;
  struct Node *next;
} Node;

/**
 * List
 * Definition of a double chained list
 */
typedef struct List {
  ListElementType elementType;
  unsigned long length;
  struct Node *first;
  struct Node *last;
} *List;

// ================================
// Functions prototypes
// ================================

/**
 * Create a list
 *
 * @return a new list
 */
List create_list(void);

/**
 * Check if a list is empty or not
 *
 * @param list
 *
 * @return true if empty
 */
bool is_empty(List list);

/**
 * Add an element at the end of the list
 *
 * @param list  the list
 * @param x  the element
 * @param elementType the type of the element
 *
 * @return the updated list
 */
List push_back_list(List list, void *x, ListElementType elementType);

/**
 * Remove the element at the end of the list
 *
 * @param list the list
 *
 * @return the list
 */
List pop_back_list(List list);

/**
 * Clear a list
 *
 * @param list the clear
 *
 * @return a new List cleared
 */
List clear_list(List list);

#endif
