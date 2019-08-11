/**
 * \file trie.h
 *
 * This file contains the declarations of trie-related functions.
 * The trie can tell if a string is in the trie or not.
 * @author Zoltan Szatmary
 *
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Trie Trie;

/** Dynamically allocates a Trie (aka struct Trie). */
Trie *trie_create();
/** Dynamically allocates a Trie (with trie_create)
 * and fills it with the elements of the given array (of strings)
 */
Trie *trie_create_from_strings(const char **strs, size_t size);
/** Inserts the string into the trie. */
void trie_insert(Trie *trie, const char *str);
/** Searches for the given string and returns true if it finds. */
bool trie_search(Trie *trie, const char *str);
/** Prints the contained strings of the trie to the given out. */
void trie_print(Trie *trie, FILE *fp);
/** Deletes and frees the dynamically allocated Trie and its nodes. */
void trie_destroy(Trie *trie);

#endif /* TRIE_H */
