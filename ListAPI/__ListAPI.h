#pragma once

/*
** THIS FILE SHOULD NOT BE MODIFIED
** See readme.txt for more details
*/

#ifndef __ListAPI
#error "You should never include this file, use ListAPI.h instead"
#endif

#include <stdlib.h>

typedef enum e_bool { False, True } Boolean;

#define List(name) t_list_##name
#define ListIterator(name) t_list_ListIterator_##name

#define ListConstruct(name) construct_##name()
#define ListDestruct(name) destruct_##name

#define IteratorOperator(name) operator_it_##name
#define IteratorValue(name) value_it_##name

#define __define_list__(name, type) \
typedef struct s_list_ListIterator_##name ListIterator(name); \
struct s_list_ListIterator_##name { \
  type elem; \
  ListIterator(name) *prev; \
  ListIterator(name) *next; \
  Boolean isEnd; \
}; \
\
\
typedef struct s_list_##name List(name); \
struct s_list_##name { \
  ListIterator(name) *__begin__; \
\
  ListIterator(name) *(*begin)(List(name) *); \
  ListIterator(name) *(*end)(List(name) *); \
  ListIterator(name) *(*find)(List(name) *, Boolean (*)(const type, const type), type); \
\
  Boolean (*empty)(List(name) *); \
  size_t (*size)(List(name) *); \
\
  type (*front)(List(name) *); \
  type (*back)(List(name) *); \
\
  void (*push_front)(List(name) *, type); \
  void (*pop_front)(List(name) *); \
  void (*push_back)(List(name) *, type); \
  void (*pop_back)(List(name) *); \
\
  void (*assign)(List(name)*, size_t, type); \
  void (*insert)(List(name) *, ListIterator(name) *it, type); \
  void (*swap)(List(name) *, List(name) *); \
\
  void (*erase)(List(name) *, ListIterator(name) *); \
  void (*clear)(List(name) *); \
\
  void (*for_each)(List(name) *, void (*)(type)); \
}; \
List(name) * construct_##name(); \
void destruct_##name(List(name) *); \
ListIterator(name) * operator_it_##name(ListIterator(name) *, int); \
type value_it_##name(ListIterator(name) *);

// Implementation of templated list
#define __implement_list__(name, type) \
static ListIterator(name) *begin_##name(List(name) *list) { \
  return list->__begin__; \
} \
\
static ListIterator(name) *end_##name(List(name) *list) { \
  return list->__begin__->prev; \
} \
\
static ListIterator(name) * find_##name(List(name) *list, Boolean (*predicate)(const type, const type), type value) { \
  ListIterator(name) *it; \
  for (it = list->begin(list); \
       it != list->end(list) && !predicate(IteratorValue(name)(it), value); \
       it = IteratorOperator(name)(it, 1)); \
  return it; \
} \
\
\
\
static Boolean empty_##name(List(name) *list) { \
  return list->begin(list) == list->end(list); \
} \
\
static size_t size_##name(List(name) *list) { \
  size_t res; \
  ListIterator(name) * it; \
  for (it = list->begin(list), res = 0; \
       it != list->end(list); \
       it = IteratorOperator(name)(it, 1), ++res); \
  return res; \
}\
\
\
\
static type front_##name(List(name) *list) { \
  return IteratorValue(name)(list->begin(list)); \
} \
\
static type back_##name(List(name) *list) { \
  ListIterator(name) *it; \
  for (it = list->begin(list); \
       it != list->end(list) && IteratorOperator(name)(it, 1) != list->end(list); \
       it = IteratorOperator(name)(it, 1)); \
  return IteratorValue(name)(it); \
}\
\
\
\
static void push_front_##name(List(name) *list, type elem) { \
  ListIterator(name) * new_element = malloc(sizeof(ListIterator(name))); \
  new_element->elem = elem; \
  new_element->prev = list->end(list); \
  new_element->next = list->begin(list); \
  new_element->prev->next = new_element; \
  new_element->isEnd = False; \
  list->__begin__ = new_element; \
} \
\
static void pop_front_##name(List(name) *list) { \
  if (list->empty(list)) \
    return ; \
  ListIterator(name) * begin = list->begin(list); \
  ListIterator(name) * newBegin = IteratorOperator(name)(begin, 1); \
  newBegin->prev = begin->prev; \
  newBegin->prev->next = newBegin; \
  list->__begin__ = newBegin; \
  free(begin); \
} \
\
static void push_back_##name(List(name) *list, type elem) { \
  ListIterator(name) * new_element = malloc(sizeof(ListIterator(name))); \
  new_element->elem = elem; \
  new_element->prev = list->end(list)->prev; \
  new_element->next = list->end(list); \
  new_element->prev->next = new_element; \
  new_element->isEnd = False; \
  if (list->empty(list)) \
    list->__begin__ = new_element; \
  list->end(list)->prev = new_element; \
} \
\
static void pop_back_##name(List(name) *list) { \
  if (list->empty(list)) \
    return ; \
  else if (list->size(list) == 1) { \
    list->pop_front(list); \
    return ; \
  } \
  ListIterator(name) * back = list->end(list)->prev; \
  ListIterator(name) * newBack = back->prev; \
  newBack->next = back->next; \
  free(back); \
} \
\
\
\
static void assign_##name(List(name) *list, size_t count, type elem) { \
  list->clear(list); \
  size_t i; \
  for (i = 0; i < count; ++i) \
    list->push_back(list, elem); \
} \
\
static void insert_##name(List(name) *list, ListIterator(name) *pos, type element) { \
  if (pos == list->end(list)) { \
    list->push_back(list, element); \
  } else if (pos == list->begin(list)) { \
    list->push_front(list, element); \
    return ; \
  } else {\
  ListIterator(name) * new_element = malloc(sizeof(ListIterator(name))); \
  new_element->elem = element; \
  new_element->prev = pos->prev; \
  new_element->next = pos; \
  pos->prev = new_element; \
  new_element->prev->next = new_element; \
  new_element->isEnd = False; \
  } \
} \
\
\
\
static void erase_##name(List(name) *list, ListIterator(name) *pos) { \
  ListIterator(name) *prev, *it; \
  for (prev = list->end(list), it = list->begin(list); \
       it != list->end(list) && it != pos; \
       prev = it, it = IteratorOperator(name)(it, 1)); \
  if (prev == list->end(list)) \
    return ; \
  prev->next = IteratorOperator(name)(it, 1); \
  free(it); \
}\
\
static void clear_##name(List(name) *list) { \
  while (!list->empty(list)) \
    pop_front_##name(list); \
}\
\
static void swap_##name(List(name) *first, List(name) *second) { \
  ListIterator(name) * backup = first->begin(first); \
  first->__begin__ = second->begin(second); \
  second->__begin__ = backup; \
} \
\
\
\
static void for_each_##name(List(name) *list, void (*func)(type elem)) { \
  ListIterator(name) *it; \
  for (it = list->begin(list); it != list->end(list); it = IteratorOperator(name)(it, 1)) \
    func(IteratorValue(name)(it)); \
} \
\
\
\
List(name) * construct_##name() { \
  List(name) *list; \
  list = malloc(sizeof(List(name))); \
  list->__begin__ = malloc(sizeof(ListIterator(name))); \
  list->__begin__->next = list->__begin__; \
  list->__begin__->prev = list->__begin__; \
  list->__begin__->elem = (type)0; \
  list->__begin__->isEnd = True; \
  list->begin = &begin_##name; \
  list->end = &end_##name; \
  list->find = &find_##name; \
  list->empty = &empty_##name; \
  list->size = &size_##name; \
  list->front = &front_##name; \
  list->back = &back_##name; \
  list->push_front = &push_front_##name; \
  list->pop_front = &pop_front_##name; \
  list->push_back = &push_back_##name; \
  list->pop_back = &pop_back_##name; \
  list->assign = &assign_##name; \
  list->insert = &insert_##name; \
  list->erase = &erase_##name; \
  list->clear = &clear_##name; \
  list->swap = &swap_##name; \
  list->for_each = &for_each_##name; \
  return list; \
}\
\
void destruct_##name(List(name) *list) { \
  list->clear(list); \
  free(list->__begin__); \
  free((void*)list); \
} \
\
ListIterator(name) * operator_it_##name(ListIterator(name) * it, int value) { \
  if (value > 0) \
    for (; !it->isEnd && value-- > 0; it = it->next); \
  else { \
    if (it->isEnd) { \
      ++value; \
      it = it->prev; \
    } \
    for (; !it->isEnd && value++ < 0; it = it->prev); \
    if (it->isEnd) \
      it = it->next; \
  } \
  return it; \
} \
\
type value_it_##name(ListIterator(name) *it) { \
  return it ? it->elem : (type) 0; \
} \


