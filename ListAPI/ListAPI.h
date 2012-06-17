#pragma once
#define __ListAPI
#include "__ListAPI.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
** Declarations of lists
** See readme.txt for more details
*/

/*
**
** You can use those functions from a list
** The first parameter is the list you want to deal with :
**
**  Return iterator to the begin of the list
**    ListIterator(name) * begin(List(name) *);
**
**  Return iterator to the end of the list
**    ListIterator(name) * end(List(name) *);
**
**  Find the first element that matchs the predicate "predicate" with value "value"
**    ListIterator(name) * find(List(name) *, bool(*)(const type , const type ) predicate, type value);
**
**  Return True if list is empty, False else
**    bool empty(List(name) *);
**
**  Return the size of the list
**    size_t size(List(name) *);
**
**  Return the value of the first element of the list
**    type front(List(name) *);
**
**  Return the value of the last element of the list
**    type back(List(name) *);
**
**  Add value "value" to the beginning of the list
**    void push_front(List(name) *, type value);
**
**  Remove the first element of the list
**    void pop_front(List(name) *);
**
**  Add value "value" to the end to the list
**    void push_back(List(name) *, type value);
**
**  Remove the last element of the list
**    void pop_back(List(name) *);
**
**  Assign "count" elements of value "value" to the list.
**    void assign(List(name) *, size_t count, type value);
**
**  Insert an element BEFORE "pos", with value "value"
**    void insert(List(name) *, ListIterator(name) *pos, type value);
**
**  Remove (ListIterator(name) *) from list
**    void erase(List(name) *, ListIterator(name) *toRemove);
**
**  Remove all elements from the list
**    void clear(List(name) *);
**
**  Apply the function "func" to each element of the list
**    void for_each(List(name) *, void(*)(type ) func);
**
**
**
**  To get and instance of the list
**    List(name) * list = ListConstruct(name);
**
**
**
**  To get or set the value of an iterator
**    ListIterator(name) * it = list->begin(list);
**    type value = IteratorValue(name)(it);
**    ++value;
**    IteratorValue(name)(it) = value;
**
**  To set the value of an iterator
**    type value = ...;
**    IteratorSetter(name)(it, value)
**
**  To increment/decrement an iterator
**    ListIterator(name) * second = IteratorOperator(name)(it, 1);
**    ListIterator(name) * third = IteratorOperator(name)(it, 2);
**    ListIterator(name) * first = IteratorOperator(name)(third, -2);
**
**
*/

__define_list__(STRING, char *)
__define_list__(INTEGER, size_t)
__define_list__(STAT, struct stat)