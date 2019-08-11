/**
 * \file list.c
 *
 * This file defines the declarations and struct HashTable from 'hashtable.h'.
 * @author Zoltan Szatmary
 *
 */

#include "hashtable.h"

struct HashTable {
    Bucket *data[HASH_SIZE];
    size_t size;
};

HashTable *hashtable_create()
{
    HashTable *htable = (HashTable*) malloc(sizeof(HashTable));
    if (htable == NULL)
        return NULL;
    memset(htable->data, 0, HASH_SIZE * sizeof(Bucket*));
    htable->size = HASH_SIZE;
    return htable;
}

static int hashtable_hash_int(int key) {
    return key % HASH_SIZE;
}

void hashtable_set_h(HashTable *htable, int key, int val, int (*hash_f)(int))
{
    int hash = hash_f(key);
    Bucket *b = htable->data[hash];
    if (b == NULL) {
        b = (Bucket*) malloc(sizeof(Bucket));
        if (b == NULL)
            return;
        b->key = key;
        b->val = val;
        b->next = NULL;
        htable->data[hash] = b;
    } else {
        Bucket *end = b;
        while (end->next != NULL && end->key != key) {
            end = end->next;
        }
        if (b == NULL) {
            b = (Bucket*) malloc(sizeof(Bucket));
            if (b == NULL)
                return;
            b->key = key;
            b->next = NULL;
            end->next = b;
        }
        b->val = val;
    }
}

void hashtable_set(HashTable *htable, int key, int val)
{
    hashtable_set_h(htable, key, val, hashtable_hash_int);
}

int *hashtable_get(HashTable *htable, int key)
{
    int hash = hashtable_hash_int(key);
    Bucket *b = htable->data[hash];
    for (Bucket *moving = b; moving != NULL; moving = moving->next) {
        if (moving->key == key)
            return &moving->val;
    }
    return NULL;
}

static void hashtable_free_bucket(Bucket *b)
{
    Bucket *moving = b, *next;
    while (moving != NULL) {
        next = moving->next;
        free(moving);
        moving = next;
    }
}

void hashtable_destroy(HashTable *htable)
{
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        if (htable->data[i] != NULL) hashtable_free_bucket(htable->data[i]);
    }
    free(htable);
}