#ifndef TRIBE_H
#define TRIBE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Trie Trie;

Trie *trie_create();
Trie *trie_create_from_strings(const char **strs, size_t size);
void trie_insert(Trie *trie, const char *str);
bool trie_search(Trie *trie, const char *str);
void trie_print(Trie *trie);
void trie_delete(Trie *trie);

#endif // TRIBE_H
