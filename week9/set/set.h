#ifndef SET_H
#define SET_H

#include <stdbool.h>

// sets are represented by 'void *'

void *empty_set(void);
void insert_element(void *, short);
bool element_exists(void const *, short);
void free_set(void *);

#endif
