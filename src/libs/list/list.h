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

/* get_length
 * Input:
 *      - List => the list to check
 * Return:
 *      - unsigned long => the length of the list
 *
 * Description:
 *      - Return the length of the list
 * */
unsigned long get_length(List list);

/**
 * Return the first element of the list
 *
 * @param list the list
 *
 * @return the first element
 */
Node *get_first_element(List list);

/**
 * Return the last element of the list
 *
 * @param list the list
 *
 * @return the last element
 */
Node *get_last_element(List list);

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
 * Add an element at the front of the list
 *
 * @param list  the list
 * @param x  the element
 * @param elementType the type of the element
 *
 * @return the updated list
 */
List push_front_list(List list, void *x, ListElementType elementType);

/**
 * Remove the element at the end of the list
 *
 * @param list the list
 *
 * @return the list
 */
List pop_back_list(List list);

/**
 * Remove the element at the start of the list
 *
 * @param list the list
 *
 * @return the list
 */
List pop_front_list(List list);

/**
 * Get a element by its index
 *
 * @param list the list
 * @param i    the index of the wanted value)
 *
 * @return return an element by its index
 */
Node *get_element_by_index(List list, int i);

/**
 * Clear a list
 *
 * @param list the clear
 *
 * @return a new List cleared
 */
List clear_list(List list);

#endif
