/**
 * \file hashtable.h
 *
 * This file contains the declarations of hashtable functions.
 * @author Zoltan Szatmary
 *
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HASH_SIZE 50

typedef struct Bucket {
    void *key;
    void *val;
    struct Bucket *next;
} Bucket;

typedef struct HashTable HashTable;

HashTable *hashtable_create();
HashTable *hashtable_create_with_functions(size_t (*hash_f)(void *), int (*cmp_f)(void *, void *));
void **hashtable_get(HashTable *htable, void *key);
bool hashtable_find(HashTable *htable, void *key);
void hashtable_destroy(HashTable *htable);

#endif /* HASHTABLE_H */
