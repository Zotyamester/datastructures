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
#include <string.h>

#define HASH_SIZE 50

typedef struct Bucket {
    int key;
    int val;
    struct Bucket *next;
} Bucket;

typedef struct HashTable HashTable;

HashTable *hashtable_create();
void hashtable_set_h(HashTable *htable, int key, int val, int (*hash_f)(int));
void hashtable_set(HashTable *htable, int key, int val);
int *hashtable_get(HashTable *htable, int key);
void hashtable_destroy(HashTable *htable);

#endif /* HASHTABLE_H */
