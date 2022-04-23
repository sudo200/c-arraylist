#include "arraylist.h"

struct arraylist {
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

arraylist * arraylist_new(void)
{
  arraylist * list = malloc(sizeof(arraylist));
  *list = (arraylist) {
    (void **)malloc(sizeof(void *)),
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

  list->array = realloc(list->array, sizeof(void *) * (len + 1));
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
  {
    *(list->array + index) = *(list->array + index +1);
  }

  list->array = realloc(list->array, sizeof(void *) * (len -1));

  return item;
}

void arraylist_destroy(arraylist * list)
{
  if(list == NULL)
    return;

  free(list->array);
  free(list);
}

arraylist * arraylist_foreach(arraylist * list, void (*func)(void *))
{
  if(list == NULL || func == NULL)
    return NULL;

  for(void ** arr = list->array; *(int *)arr; arr++)
    func(*arr);

  return list;
}

