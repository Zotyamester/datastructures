/**
 * \file vector.c
 *
 * This file defines the declarations and struct Vector from 'vector.h'.
 * @author Zoltan Szatmary
 *
 */

#include "vector.h"
#include <string.h>

struct Vector {
    int *data;
    size_t capacity;
    size_t size;
};

Vector *vector_create()
{
    Vector *vector = (Vector*) malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;
    vector->capacity = VECTOR_DEFAULT_CAPACITY;
    vector->size = 0;
    vector->data = (int*) malloc(vector->capacity * sizeof(int));
    if (vector->data == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}
Vector *vector_create_with_size(size_t size)
{
    Vector *vector = (Vector*) malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;
    vector->capacity = size * 2;
    vector->size = size;
    vector->data = (int*) malloc(vector->capacity * sizeof(int));
    if (vector->data == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}
Vector *vector_create_from_array(int *array, size_t size)
{
    Vector *vector = vector_create_with_size(size);
    if (vector == NULL)
        return NULL;
    memcpy(vector->data, array, size * sizeof(int));
    return vector;
}
Vector *vector_scan(FILE *fp)
{
    Vector *vector = vector_create();
    if (vector == NULL)
        return NULL;
    int n;
    while (fscanf(fp, "%d", &n) == 1) {
        vector_push_back(vector, n);
    }
    return vector;
}
Vector *vector_copy(Vector *vector)
{
    Vector *new_vector = vector_create_with_size(vector->size);
    if (new_vector == NULL)
        return NULL;
    memcpy(new_vector->data, vector->data, vector->size * sizeof(int));
    return new_vector;
}
Vector *vector_sub(Vector *vector, size_t from, size_t to)
{
    size_t size = to - from;
    Vector *new_vector = vector_create_with_size(vector->size);
    if (new_vector == NULL)
        return NULL;
    for (size_t i = 0; i < size; ++i)
        new_vector->data[i] = vector->data[from + i];
    return new_vector;
}
void vector_link(Vector *vector, Vector *other)
{
    if (vector_resize(vector, vector->size + other->size))
        memcpy(vector->data + vector->size, other->data, other->size * sizeof(int));
}
size_t vector_size(Vector *vector)
{
    return vector->size;
}
bool vector_empty(Vector *vector)
{
    return vector->size == 0;
}
void vector_reverse(Vector *vector)
{
    size_t n = vector->size / 2;
    for (size_t i = 0; i < n; ++i) {
        int temp = vector->data[i];
        vector->data[i] = vector->data[vector->size - 1 - i];
        vector->data[vector->size - 1 -i] = temp;
    }
}
void vector_insert(Vector *vector, size_t index, int data)
{
    if (vector->size + 1 == vector->capacity) {
        size_t capacity = vector->capacity * 2;
        int *arr = (int*) malloc(capacity * sizeof(int));
        if (arr == NULL)
            return;
        vector->capacity = capacity;
        memcpy(arr, vector->data, vector->size * sizeof(int));
        free(vector->data);
        vector->data = arr;
    }
    for (size_t i = vector->size; i > index; --i)
        vector->data[i] = vector->data[i - 1];
    vector->data[index] = data;
    ++vector->size;
}
void vector_push_front(Vector *vector, int data)
{
    if (vector->size + 1 == vector->capacity) {
        size_t capacity = vector->capacity * 2;
        int *arr = (int*) malloc(capacity * sizeof(int));
        if (arr == NULL)
            return;
        vector->capacity = capacity;
        memcpy(arr, vector->data, vector->size * sizeof(int));
        free(vector->data);
        vector->data = arr;
    }
    for (size_t i = vector->size; i > 0; --i)
        vector->data[i] = vector->data[i - 1];
    vector->data[0] = data;
    ++vector->size;
}
void vector_push_back(Vector *vector, int data)
{
    if (vector->size + 1 == vector->capacity) {
        size_t capacity = vector->capacity * 2;
        int *arr = (int*) malloc(capacity * sizeof(int));
        if (arr == NULL)
            return;
        vector->capacity = capacity;
        memcpy(arr, vector->data, vector->size * sizeof(int));
        free(vector->data);
        vector->data = arr;
    }
    vector->data[vector->size++] = data;
}
void vector_pop_front(Vector *vector)
{
    size_t end = vector->size - 1;
    for (size_t i = 0; i < end; ++i)
        vector[i] = vector[i + 1];
    --vector->size;
}
void vector_pop_back(Vector *vector)
{
    --vector->size;
}
int vector_front(Vector *vector)
{
    return vector->data[0];
}
int vector_back(Vector *vector)
{
    return vector->data[vector->size - 1];
}
int *vector_get(Vector *vector, size_t index)
{
    return &vector->data[index];
}
VectorIter vector_begin(Vector *vector)
{
    return vector->data;
}
VectorIter vector_end(Vector *vector)
{
    return vector->data + vector->size;
}
inline VectorIter vector_next(VectorIter iter)
{
    return ++iter;
}
void vector_print(Vector *vector, FILE *fp)
{
    for (size_t i = 0; i < vector->size; ++i)
        fprintf(fp, "%d ", vector->data[i]);
}
void vector_clear(Vector *vector)
{
    vector->capacity = VECTOR_DEFAULT_CAPACITY;
    vector->size = 0;
    int *arr = (int*) malloc(vector->capacity * sizeof(int));
    if (arr == NULL)
        return;
    free(vector->data);
    vector->data = arr;
}
bool vector_resize(Vector *vector, size_t size)
{
    if (size >= vector->capacity) {
        size_t capacity = vector->capacity * 2;
        while (size >= capacity)
            capacity = vector->capacity * 2;
        int *arr = (int*) malloc(capacity * sizeof(int));
        if (arr == NULL)
            return false;
        vector->capacity = capacity;
        memcpy(arr, vector->data, vector->size * sizeof(int));
        free(vector->data);
        vector->data = arr;
    }
    vector->size = size;
    return true;
}
size_t vector_to_array(Vector *vector, int **array_ptr)
{
    int *array = (int*) malloc(vector->size * sizeof(int));
    if (array == NULL) {
        *array_ptr = NULL;
        return 0;
    }
    memcpy(array, vector->data, vector->size * sizeof(int));
    return vector->size;
}
void vector_destroy(Vector *vector)
{
    free(vector->data);
    free(vector);
}
