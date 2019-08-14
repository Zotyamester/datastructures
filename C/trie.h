/**
 * \file trie.h
 *
 * This file contains the declarations of trie-related functions.
 * The trie can map a string to a function.
 * @author Zoltan Szatmary
 *
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Trie Trie;

typedef void (*function)(void);

/** Dynamically allocates a Trie (aka struct Trie). */
Trie *trie_create();
/** Inserts the string into the trie. */
void trie_insert(Trie *trie, const char *str, function func);
/** Searches for the given string and returns true if it finds. */
function trie_find(Trie *trie, const char *str);
/** Prints the contained strings of the trie to the given out. */
void trie_print(Trie *trie, FILE *fp);
/** Deletes and frees the dynamically allocated Trie and its nodes. */
void trie_destroy(Trie *trie);

#endif /* TRIE_H */
