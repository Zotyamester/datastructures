#include "hashtable.h"

struct HashTable {
    Bucket *data[HASH_SIZE];
    size_t size;
};

HashTable *create_hashtable() {
    HashTable *htable = (HashTable*) malloc(sizeof(HashTable));
    if(htable == NULL) return NULL;
    memset(htable->data, 0, HASH_SIZE * sizeof(Bucket*));
    htable->size = HASH_SIZE;
    return htable;
}

static int hash_int(int key) {
    return key % HASH_SIZE;
}

void insert_hashtable_h(HashTable *htable, int key, int val, int (*hash_f)(int)) {
    int hash = hash_f(key);
    Bucket *b = htable->data[hash];
    if(b == NULL) {
        b = (Bucket*) malloc(sizeof(Bucket));
        if(b == NULL) return;
        b->key = key;
        b->val = val;
        b->next = NULL;
        htable->data[hash] = b;
    } else {
        Bucket *end = b;
        while(end->next != NULL) {
            if(end->key == key) return;
            end = end->next;
        }
        b = (Bucket*) malloc(sizeof(Bucket));
        if(b == NULL) return;
        b->key = key;
        b->val = val;
        b->next = NULL;
        end->next = b;
    }
}

void insert_hashtable(HashTable *htable, int key, int val) {
    insert_hashtable_h(htable, key, val, hash_int);
}

int get_hashtableitem(HashTable *htable, int key) {
    int hash = hash_int(key);
    Bucket *b = htable->data[hash];
    for(Bucket *moving = b; moving != NULL; moving = moving->next) {
        if(moving->key == key) return moving->val;
    }
    return 0;
}

static void free_bucket(Bucket *b) {
    Bucket *moving = b, *next;
    while(moving != NULL) {
        next = moving->next;
        free(moving);
        moving = next;
    }
}

void delete_hashtable(HashTable *htable) {
    for(int i = 0; i < HASH_SIZE; ++i) {
        if(htable->data[i] != NULL) free_bucket(htable->data[i]);
    }
    free(htable);
}
