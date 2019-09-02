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
    void **data;
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
    vector->data = (void *) malloc(vector->capacity * sizeof(void *));
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
    vector->data = (void *) malloc(vector->capacity * sizeof(void *));
    if (vector->data == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

Vector *vector_create_from_array(void **array, size_t size)
{
    Vector *vector = vector_create_with_size(size);
    if (vector == NULL)
        return NULL;
    memcpy(vector->data, array, size * sizeof(void *));
    return vector;
}

Vector *vector_scan(FILE *fp, void *(*scanner)(FILE *))
{
    Vector *vector = vector_create();
    if (vector == NULL)
        return NULL;
    void *temp;
    while ((temp = scanner(fp)) != NULL) {
        vector_push_back(vector, temp);
    }
    return vector;
}

Vector *vector_copy(Vector *vector)
{
    Vector *new_vector = vector_create_with_size(vector->size);
    if (new_vector == NULL)
        return NULL;
    memcpy(new_vector->data, vector->data, vector->size * sizeof(void *));
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

void vector_cat(Vector *vector, Vector *other)
{
    if (vector_resize(vector, vector->size + other->size))
        memcpy(vector->data + vector->size, other->data, other->size * sizeof(void *));
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
        void *temp = vector->data[i];
        vector->data[i] = vector->data[vector->size - 1 - i];
        vector->data[vector->size - 1 -i] = temp;
    }
}

static bool vector_double(Vector *vector)
{
    size_t capacity = vector->capacity * 2;
    void **arr = (void *) malloc(capacity * sizeof(void *));
    if (arr == NULL)
        return false;
    vector->capacity = capacity;
    memcpy(arr, vector->data, vector->size * sizeof(void *));
    free(vector->data);
    vector->data = arr;
    return true;
}

void vector_insert(Vector *vector, size_t index, void *data)
{
    if (vector->size + 1 == vector->capacity && !vector_double(vector))
        return;
    for (size_t i = vector->size; i > index; --i)
        vector->data[i] = vector->data[i - 1];
    vector->data[index] = data;
    ++vector->size;
}

void vector_push_front(Vector *vector, void *data)
{
    if (vector->size + 1 == vector->capacity && !vector_double(vector))
        return;
    for (size_t i = vector->size; i > 0; --i)
        vector->data[i] = vector->data[i - 1];
    vector->data[0] = data;
    ++vector->size;
}

void vector_push_back(Vector *vector, void *data)
{
    if (vector->size + 1 == vector->capacity && !vector_double(vector))
        return;
    vector->data[vector->size++] = data;
}

void vector_pop_front(Vector *vector)
{
    for (size_t i = 1; i < vector->size; ++i)
        vector->data[i - 1] = vector->data[i];
    --vector->size;
}

void vector_pop_back(Vector *vector)
{
    --vector->size;
}

void *vector_front(Vector *vector)
{
    return vector->data[0];
}

void *vector_back(Vector *vector)
{
    return vector->data[vector->size - 1];
}

void **vector_get(Vector *vector, size_t index)
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

void vector_print(Vector *vector, FILE *fp, void (*printer)(FILE *, void *))
{
    for (size_t i = 0; i < vector->size; ++i) {
        printer(fp, vector->data[i]);
        putc(' ', fp);
    }
}

void vector_free_data(Vector *vector)
{
    for (size_t i = 0; i < vector->size; ++i) {
        free(vector->data[i]);
        vector->data[i] = NULL;
    }
}

void vector_clear(Vector *vector)
{
    vector->capacity = VECTOR_DEFAULT_CAPACITY;
    vector->size = 0;
    void **arr = (void *) malloc(vector->capacity * sizeof(void *));
    if (arr == NULL)
        return;
    free(vector->data);
    vector->data = arr;
}

size_t vector_to_array(Vector *vector, void ***array_ptr)
{
    void **array = (void *) malloc(vector->size * sizeof(void *));
    if (array == NULL) {
        *array_ptr = NULL;
        return 0;
    }
    memcpy(array, vector->data, vector->size * sizeof(void *));
    return vector->size;
}

void vector_remove_item(Vector *vector, void *data)
{
    size_t i;
    for (i = 0; i < vector->size; ++i)
        if (vector->data[i] == data)
            break;
    if (i == vector->size)
        return;
    for (++i; i < vector->size; ++i)
        vector->data[i - 1] = vector->data[i];
    --vector->size;
}

bool vector_resize(Vector *vector, size_t size)
{
    if (size >= vector->capacity) {
        size_t capacity = vector->capacity * 2;
        while (size >= capacity)
            capacity = vector->capacity * 2;
        void **arr = (void *) malloc(capacity * sizeof(void *));
        if (arr == NULL)
            return false;
        vector->capacity = capacity;
        memcpy(arr, vector->data, vector->size * sizeof(void *));
        free(vector->data);
        vector->data = arr;
    }
    vector->size = size;
    return true;
}

void vector_destroy(Vector *vector)
{
    free(vector->data);
    free(vector);
}
