/**
 * \file hashtable.h
 *
 * This file contains the declarations of hashtable functions.
 * @author Zoltan Szatmary
 *
 **/

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

HashTable *create_hashtable();
void set_hashtable_h(HashTable *htable, int key, int val, int (*hash_f)(int));
void set_hashtable(HashTable *htable, int key, int val);
int *get_hashtableitem(HashTable *htable, int key);
void delete_hashtable(HashTable *htable);

#endif // HASHTABLE_H
