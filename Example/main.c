#include "ListAPI.h"

#include <string.h>
#include <stdio.h>
void dump(char *str) { printf("%s\n", str); }
Boolean cmp(char const * first, char const *sec) { return !strcmp(first, sec); }

#include <assert.h>
#define BEGIN "BEGIN"
#define MIDDLE "MIDDLE"
#define END "END"
int main() {
  List(STRING) *lst = ListConstruct(STRING);

  // Adding values to the list
  lst->assign(lst, 10, MIDDLE);
  lst->push_back(lst, END);
  lst->push_front(lst, BEGIN);

  // Getting the first iterator with begin
  // Getting the first value with front 
  // Compare them with IteratorValue(NAME)
  ListIterator(STRING) *begin = lst->begin(lst);
  char *front = lst->front(lst);
  assert(front == IteratorValue(STRING)(begin));
  assert(!strcmp(front, BEGIN));

  // Getting the last iterator with end
  // Getting the last value with back 
  // Compare them with IteratorValue(NAME)
  // As end is the iterator AFTER the last one, we must use IteratorOperator(it, -1)
  ListIterator(STRING) *end = lst->end(lst);
  char *back = lst->back(lst);
  assert(back == IteratorValue(STRING)(IteratorOperator(STRING)(end, -1)));
  assert(!strcmp(back, END));

  // Checking if empty is valid, and if size is really 12
  assert(lst->empty(lst) == False);
  assert(lst->size(lst) == 12);
  
  // Removing first and last elements
  lst->pop_front(lst);
  lst->pop_back(lst);

  assert(lst->size(lst) == 10);
  assert(!strcmp(lst->front(lst), MIDDLE));

  // Clearing the whole list
  lst->clear(lst);
  assert(lst->size(lst) == 0);
  assert(lst->empty(lst) == True);

  // Adding a few elements
  lst->push_back(lst, BEGIN);
  lst->push_back(lst, MIDDLE);
  lst->push_back(lst, END);

  // Finding iterator with find
  ListIterator(STRING) *middle = lst->find(lst, &cmp, MIDDLE);
  assert(!strcmp(IteratorValue(STRING)(middle), MIDDLE));

  // Inserting an element before the middle iterator
  lst->insert(lst, middle, BEGIN);
  lst->pop_front(lst);
  assert(lst->size(lst) == 3);

  // Dumping the list with for_each
  lst->for_each(lst, &dump);

  // Destructing the list to get all your memory back :-)
  ListDestruct(STRING)(lst);

  printf("Everything is working ! At least, it seems\n");


  // And you can, of course, have different types !!
  List(INTEGER) * intList = ListConstruct(INTEGER);

  return 0;
}