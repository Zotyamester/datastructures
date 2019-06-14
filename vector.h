#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VECTOR_DEFAULT_CAPACITY 25

typedef struct Vector Vector;

Vector *vector_create();
Vector *vector_create_with_size(size_t size);
Vector *vector_create_from_array(int *array, size_t size);
Vector *vector_scan(FILE *fp);
Vector *vector_copy(Vector *vector);
Vector *vector_sub(Vector *vector, int from, int to);
void vector_link(Vector *vector, Vector *other);
size_t vector_get_size(Vector *vector);
bool vector_is_empty(Vector *vector);
void vector_reverse(Vector *vector);
void vector_insert(Vector *vector, int index, int data);
void vector_push_front(Vector *vector, int data);
void vector_push_back(Vector *vector, int data);
void vector_pop_front(Vector *vector);
void vector_pop_back(Vector *vector);
int vector_get_front(Vector *vector);
int vector_get_back(Vector *vector);
int *vector_get_index(Vector *vector, int index);
void vector_print(Vector *vector, FILE *fp);
void vector_clear(Vector *vector);
bool vector_resize(Vector *vector, size_t size);
size_t vector_to_array(Vector *vector, int **array_ptr);
void vector_delete(Vector *vector);

#endif /* VECTOR_H */
