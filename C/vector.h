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

typedef void ** VectorIter;

typedef struct Vector Vector;

/** Dynamically allocates a Vector. */
Vector *vector_create();

/** Creates a vector with 'size' zeros. */
Vector *vector_create_with_size(size_t size);

/** Dynamically allocates a Vector and initializes it with the given array. */
Vector *vector_create_from_array(void **array, size_t size);

/** Scans for a vector of data in the given in and makes a vector. */
Vector *vector_scan(FILE *fp, void *(*scanner)(FILE *));

/** Makes a deep copy of the given vector. */
Vector *vector_copy(Vector *vector);

/** Makes a sublist of the given vector. The subvector will be a from left-closed, from right-open interval. */
Vector *vector_sub(Vector *vector, size_t from, size_t to);

/** Links a vector to another. */
void vector_cat(Vector *vector, Vector *other);

/** Returns the size of the vector. It runs in O(1) since it always keeps track of the size. */
size_t vector_size(Vector *vector);

/** Returns with a bool indicating whether the vector is empty or not. */
bool vector_empty(Vector *vector);

/** Reverses the vector. */
void vector_reverse(Vector *vector);

/** Inserts a node to the given position (index from 0) of the vector. */
void vector_insert(Vector *vector, size_t index, void *data);

/** Adds a new node to the head of the vector. */
void vector_push_front(Vector *vector, void *data);

/** Adds a new node to the back of the vector. */
void vector_push_back(Vector *vector, void *data);

/** Deletes the first value of the vector. */
void vector_pop_front(Vector *vector);

/** Deletes the last value of the vector. */
void vector_pop_back(Vector *vector);

/** Retrieves the first value of the vector. */
void *vector_front(Vector *vector);

/** Retrieves the last value of the vector. */
void *vector_back(Vector *vector);

/** Gets the (pointer to it) item form the given position (index from 0 to the (size - 1)th) of the vector. */
void **vector_get(Vector *vector, size_t index);

/** Returns an 'iterator' (VectorIter). */
VectorIter vector_begin(Vector *vector);

/** Returns with the end pointer of the vector. */
VectorIter vector_end(Vector *vector);

/** Steps one with the iterator. Returns with the next element in the vector. */
inline VectorIter vector_next(VectorIter iter)
{
    return ++iter;
}

/** Prints the vector to the give out separated by spaces (without an ending '\n'). */
void vector_print(Vector *vector, FILE *fp, void (*printer)(FILE *, void *));

/** Allocates an array based on the elements of the vector. */
size_t vector_to_array(Vector *vector, void ***array_ptr);

/** Searches for the specified value and if it finds then removes it. */
void vector_remove_item(Vector *vector, void *data);

/**
 * Calls 'free()' for each 'void *' element and then zeroes them out.
 * Warnings:
 *   - It doesn't work if not all of the pointers point to dynamically allocated memory.
 *   - It doesn't change the size of the vector.
 */
void vector_free_data(Vector *vector);

/** Clears the vector. */
void vector_clear(Vector *vector);

/** Resizes the vector's space. */
bool vector_resize(Vector *vector, size_t size);

/** Frees all dynamically allocated space (including the struct itself) */
void vector_destroy(Vector *vector);

#endif /* VECTOR_H */
