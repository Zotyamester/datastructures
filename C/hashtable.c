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
    size_t (*hash_f)(void *);
    int (*cmp_f)(void *, void *);
};

static size_t hashtable_default_hash(void *key)
{
    return ((size_t)key) % HASH_SIZE;
}

static int hashtable_default_cmp(void *a, void *b)
{
    size_t av = (size_t) a;
    size_t bv = (size_t) b;
    if (av < bv)
        return -1;
    return av > bv;
}

HashTable *hashtable_create()
{
    return hashtable_create_with_functions(hashtable_default_hash, hashtable_default_cmp);
}

HashTable *hashtable_create_with_functions(size_t (*hash_f)(void *), int (*cmp_f)(void *, void *))
{
    HashTable *htable = (HashTable *) malloc(sizeof(HashTable));
    if (htable == NULL)
        return NULL;
    memset(htable->data, NULL, HASH_SIZE * sizeof(Bucket *));
    htable->size = HASH_SIZE;
    htable->hash_f = hash_f;
    htable->cmp_f = cmp_f;
    return htable;
}

void **hashtable_get(HashTable *htable, void *key)
{
    size_t hash = htable->hash_f(key);
    Bucket *prev = NULL, *bucket;
    for (bucket = htable->data[hash]; bucket != NULL && htable->cmp_f(bucket->key, key) != 0; prev = bucket, bucket = bucket->next);
    if (bucket == NULL) {
        bucket = (Bucket *) malloc(sizeof(Bucket));
        if (bucket == NULL)
            return NULL;
        bucket->key = key;
        bucket->val = NULL;
        bucket->next = NULL;
        if (prev != NULL)
            prev->next = bucket;
        else
            htable->data[hash] = bucket;
    }
    return &bucket->val;
}
/* Same with multiple indirection
void **hashtable_get(HashTable *htable, int key)
{
    size_t hash = htable->hash_f(key);
    Bucket **bp;
    for (bp = &htable->data[hash]; (*bp) != NULL && (*bp)->key != key; bp = &(*bp)->next);
    if ((*bp) == NULL) {
        (*bp) = (Bucket *) malloc(sizeof(Bucket));
        if ((*bp) == NULL)
            return NULL;
        (*bp)->key = key;
        (*bp)->val = 0;
        (*bp)->next = NULL;
    }
    return &(*bp)->val;
}*/

bool hashtable_find(HashTable *htable, void *key)
{
    size_t hash = htable->hash_f(key);
    Bucket *bucket;
    for (bucket = htable->data[hash]; bucket != NULL && htable->cmp_f(bucket->key, key) != 0; bucket = bucket->next);
    return bucket != NULL;
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
        if (htable->data[i] != NULL)
            hashtable_free_bucket(htable->data[i]);
    }
    free(htable);
}
