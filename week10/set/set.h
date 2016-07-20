#ifndef SET_H
#define SET_H

#include <stdbool.h>

// sets are represented by 'void *'

void *empty_set(void);
void insert_element(void *, long long);
bool element_exists(void const *, long long);
void free_set(void *);

#endif
