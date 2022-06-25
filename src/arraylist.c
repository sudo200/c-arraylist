#include <arraylist.h>

struct arraylist {
  allocator_t alloc;
  deallocator_t dealloc;
  void ** array;
};

size_t arraylist_getlength(arraylist * list)
{
  if(list == NULL)
    return 0;

  size_t len = 1;
  for(void ** arr = list->array; *(int *)arr; arr++, len++);
  return len;
}

#ifndef NO_STDLIB
arraylist * arraylist_new(void)
{
  return arraylist_new_custom_alloc(malloc, free);
}
#endif//NO_STDLIB

arraylist * arraylist_new_custom_alloc(allocator_t alloc, deallocator_t dealloc)
{
  arraylist * list = (arraylist *) alloc(sizeof(arraylist));
  *list = (arraylist) {
    alloc,
    dealloc,
    (void **) alloc(sizeof(void *)),
  };

  *(list->array) = NULL;

  return list;
}

void * arraylist_get(arraylist * list, size_t index)
{
  if(list == NULL)
    return NULL;

  size_t len = arraylist_getlength(list);
  if(index >= len)
    return NULL;

  return *(list->array + index);
}

arraylist * arraylist_add(arraylist * list, void * item)
{
  if(list == NULL)
    return NULL;

  size_t len = arraylist_getlength(list);

  void ** newarray = (void **) memcpy(
      list->alloc(sizeof(void *) * (len + 1)),
      list->array,
      sizeof(void *) * len
      );
  list->dealloc(list->array);
  list->array = newarray;

  *(list->array + len-1) = item;
  *(list->array + len) = NULL;
  return list;
}

void * arraylist_remove(arraylist * list, size_t i)
{
  if(list == NULL)
    return NULL;

  size_t len = arraylist_getlength(list);

  if(i >= len)
    return NULL;

  void * item = *(list->array + i);
  for(size_t index = i; index < len; index++)
    *(list->array + index) = *(list->array + index +1);

  void ** newarray = (void **) memcpy(
      list->alloc(sizeof(void *) * (len - 1)),
      list->array,
      sizeof(void *) * (len - 1)
      );
  list->dealloc(list->array);
  list->array = newarray;

  return item;
}

void arraylist_destroy(arraylist * list)
{
  if(list == NULL)
    return;

  list->dealloc(list->array);
  list->dealloc(list);
}

arraylist * arraylist_foreach(arraylist * list, void (*func)(void *))
{
  if(list == NULL)
    return NULL;
  
  if(func == NULL)
    return list;

  for(void ** arr = list->array; *(int *)arr; arr++)
    func(*arr);

  return list;
}

