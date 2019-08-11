/**
 * \file vector.h
 *
 * This file contains the declarations of vector-related functions.
 * The vector is a dynamic array.
 * @author Zoltan Szatmary
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VECTOR_DEFAULT_CAPACITY 25

typedef int * VectorIter;

typedef struct Vector Vector;

Vector *vector_create();
Vector *vector_create_with_size(size_t size);
Vector *vector_create_from_array(int *array, size_t size);
Vector *vector_scan(FILE *fp);
Vector *vector_copy(Vector *vector);
Vector *vector_sub(Vector *vector, size_t from, size_t to);
void vector_link(Vector *vector, Vector *other);
size_t vector_size(Vector *vector);
bool vector_empty(Vector *vector);
void vector_reverse(Vector *vector);
void vector_insert(Vector *vector, size_t index, int data);
void vector_push_front(Vector *vector, int data);
void vector_push_back(Vector *vector, int data);
void vector_pop_front(Vector *vector);
void vector_pop_back(Vector *vector);
int vector_front(Vector *vector);
int vector_back(Vector *vector);
int *vector_get(Vector *vector, size_t index);
VectorIter vector_begin(Vector *vector);
VectorIter vector_end(Vector *vector);
extern inline VectorIter vector_next(VectorIter iter);
void vector_print(Vector *vector, FILE *fp);
void vector_clear(Vector *vector);
bool vector_resize(Vector *vector, size_t size);
size_t vector_to_array(Vector *vector, int **array_ptr);
void vector_destroy(Vector *vector);

#endif /* VECTOR_H */
