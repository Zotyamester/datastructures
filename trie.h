#ifndef TRIBE_H
#define TRIBE_H

#include <stdbool.h>

typedef struct Trie Trie;

Trie *trie_create();
Trie *trie_create_from_strings(const char **strs);
void trie_insert(Trie *trie, const char *str);
bool trie_search(Trie *trie, const char *str);
void trie_delete(Trie *trie);

#endif // TRIBE_H
