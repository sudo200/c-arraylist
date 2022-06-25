#include <stdio.h>

#include <arraylist.h>

void myFunc(void *ptr)
{
  char * str = (char *)ptr;
  puts(str);
}

int main()
{
  arraylist * list = arraylist_new();

  arraylist_add(list, "Hello");
  arraylist_add(list, "there!");
  arraylist_add(list, "my friends");

  puts((const char *) arraylist_get(list, 2));

  puts((const char *) arraylist_remove(list, 2));

  arraylist_foreach(list, myFunc);
  
  arraylist_destroy(list);

  return 0;
}

