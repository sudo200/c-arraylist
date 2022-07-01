#include <arraylist.h>

struct arraylist {
  alloc_t alloc;
  dealloc_t dealloc;

  void ** array;
  size_t len;
};


void * __resize(alloc_t alloc, dealloc_t dealloc, void * ptr, size_t bytes_to_copy, size_t bytes_to_alloc)
{
  void * newptr = memmove(
        alloc(bytes_to_alloc),
        ptr,
        bytes_to_copy
      );
  dealloc(ptr);
  return newptr;
}


size_t arraylist_getlength(arraylist * list)
{
  if(list == NULL)
    return 0;

  return list->len;
}

#ifndef NO_STDLIB
arraylist * arraylist_new(void)
{
  return arraylist_new_custom_alloc(malloc, free);
}
#endif//NO_STDLIB

arraylist * arraylist_new_custom_alloc(alloc_t alloc, dealloc_t dealloc)
{
  arraylist * list = (arraylist *) alloc(sizeof(arraylist));
  *list = (arraylist) {
    alloc,
    dealloc,

    NULL,
    0,
  };

  return list;
}

void * arraylist_get(arraylist * list, size_t index)
{
  if(list == NULL)
    return NULL;

  if(index >= list->len)
    return NULL;

  return list->array[index];
}

arraylist * arraylist_add(arraylist * list, void * item)
{
  if(list == NULL)
    return NULL;

  if(list->len > 0)
    list->array = (void **) __resize(
        list->alloc,
        list->dealloc,
        list->array,
        list->len * sizeof(void *),
        (list->len + 1) * sizeof(void *)
        );
  else
    list->array = (void **) malloc(sizeof(void *));

  list->array[list->len] = item;
  list->len = list->len + 1;
  
  return list;
}

void * arraylist_remove(arraylist * list, size_t i)
{
  if(list == NULL)
    return NULL;

  if(i >= list->len)
    return NULL;

  void * item = list->array[i];

  list->len = list->len - 1;

  for(size_t index = i; index < list->len; index++)
    list->array[index] = list->array[index + 1];

  list->array = __resize(
      list->alloc,
      list->dealloc,
      list->array,
      (list->len) * sizeof(void *),
      (list->len + 1) * sizeof(void *)
      );

  return item;
}

void arraylist_destroy(arraylist * list)
{
  if(list == NULL)
    return;

  if(list->len > 0)  list->dealloc(list->array);
  list->dealloc(list);
}

arraylist * arraylist_foreach(arraylist * list, void (*func)(void *))
{
  if(list == NULL)
    return NULL;
  
  if(func == NULL)
    return list;

  for(size_t i = 0; i < list->len; i++)
    func(list->array[i]);

  return list;
}

