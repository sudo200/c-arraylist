#ifndef  ARRAYLIST_H
#define  ARRAYLIST_H

#ifndef NO_STDLIB
#include <stdlib.h>
#endif//NO_STDLIB

#include <string.h>

typedef struct arraylist arraylist;


typedef void * (*allocator_t)(size_t);
typedef void (*deallocator_t)(void *);

/**
 * Get the length of the arraylist
 */
size_t arraylist_getlength(arraylist * list);

#ifndef NO_STDLIB
/**
 * Creates a new arraylist.
 *
 * Uses malloc to allocate and free to deallocate.
 * If you wanna specify your own, use `arraylist_new_custom_alloc()`!
 *
 * **Only usable with stdlib.h from libc!**
 */
arraylist * arraylist_new(void);
#endif//NO_STDLIB

/**
 * Creates a new arraylist with custom allocator and deallocator functions.
 *
 * Useful for environments, where malloc and free cannot be used.
 */
arraylist * arraylist_new_custom_alloc(allocator_t alloc, deallocator_t dealloc);

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

