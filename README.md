Informations
-------
Implementation of templated std::list in C.  
Of course, templates is only preprocessed code but it works quite well.  
The classics < > are replaced by ( )

Usage
-------
When you want to add a new type of list, you must declare it.

To do so, just add the following lines to ListAPI.c and ListAPI.h
```c
  __define_list__(name, type)     // In ListAPI.h
  __implement_list__(name, type)  // In ListAPI.c
```
Where `name` is an ID (`STRING`, `INTEGER`, etc.) and `type` the type of the linked list (`char *`, `int`, `struct stat`, etc.)
To get more informations about how to use it, read `ListAPI.h` comments.

Warning
-------
- `__ListAPI.h` : DO NOT TOUCH THIS, UNLESS YOU KNOW WHAT YOU DO
- I created this just for fun, maybe it doesn't work as well as I think !

Example
-------

ListAPI.c : `__implement_list__(STRING, char *)`  
ListAPI.h : `__define_list__(STRING, char *)`  
main.c :
```c
    List(STRING) *strList = ListConstruct(STRING);
    strList->push_back(strList, "First Element");
    ListIterator(STRING) *it = strList->begin(strList);
    //...
    ListDestruct(STRING)(strList);
```

Read the sample code for more information.
