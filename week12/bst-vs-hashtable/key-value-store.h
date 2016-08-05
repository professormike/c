#ifndef KEY_VALUE_STORE_H
#define KEY_VALUE_STORE_H

void insert_key_value(void *, char const *, double);
double retrieve_value(void const *, char const *);
void *empty_key_value_store(void);
void free_key_value_store(void *);

#endif
