#include <stdio.h>

#include <arraylist.h>

void myFunc(void *ptr)
{
  char * str = (char *)ptr;
  puts(str);
}

void normal()
{
  arraylist * list = arraylist_new();

  puts("Length out of the box:");
  printf("%lu\n", arraylist_getlength(list));

  puts("Adding Elements:");
  arraylist_add(list, "Hello");
  arraylist_add(list, "there!");
  arraylist_add(list, "my friends");

  puts("Length after adding 3 Elements:");
  printf("%lu\n", arraylist_getlength(list));

  puts("Getting 3. Element:");
  puts((const char *) arraylist_get(list, 2));

  puts("Removing 2. Element:");
  puts((const char *) arraylist_remove(list, 1));

  puts("Listing Elements:");
  arraylist_foreach(list, myFunc);
  
  arraylist_destroy(list);
}

void ackerman()
{
  arraylist * list = arraylist_new();
  
  puts("Adding 100000 elements...");
  for(size_t i = 0; i < 100000; ++i)
    arraylist_add(list, (void *) i);
  puts("done\n");

  printf("Length: %lu\n", arraylist_getlength(list));
  printf("Index 42069: %lu\n\n", (size_t) arraylist_get(list, 42069));

  arraylist_destroy(list);
}

int main()
{
  //normal();
  ackerman();

  return 0;
}

