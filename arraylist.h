#ifndef  ARRAYLIST_H
#define  ARRAYLIST_H

#include <stdlib.h>
#include <string.h>

typedef struct arraylist arraylist;

/**
 * Get the length of the arraylist
 */
size_t arraylist_getlength(arraylist * list);

/**
 * Creates a new arraylist.
 */
arraylist * arraylist_new(void);

/**
 * Get an item from the arraylist at given index.
 * If the index is out of bounds, NULL is returned.
 */
void * arraylist_get(arraylist * list, size_t index);

/**
 * Add an item to the end of the list.
 */
arraylist * arraylist_add(arraylist * list, void * item);

/**
 * Remove an item from the list at given index.
 * If index out of bounds, NULL is returned.
 * Else, the element ist returned.
 */
void * arraylist_remove(arraylist * list, size_t index);

/**
 * Frees the list from memory.
 * Warning: Stored pointers are not deallocated!
 */
void arraylist_destroy(arraylist * list);

/**
 * Executes given function for each element.
 */
arraylist * arraylist_foreach(arraylist * list, void (*func)(void *));

#endif// ARRAYLIST_H

