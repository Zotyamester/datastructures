/**
 * \file trie.c
 *
 * This file defines the declarations and struct Trie and TrieNode from 'trie.h'.
 * @author Zoltan Szatmary
 *
 */

#include "trie.h"
#include <string.h>

typedef struct TrieNode {
    bool valid;
    struct TrieNode *links[128];
} TrieNode;

struct Trie {
    TrieNode *root;
};

Trie *trie_create()
{
    Trie *trie = (Trie*) malloc(sizeof(Trie));
    if (trie == NULL)
        return NULL;
    trie->root = (TrieNode*) malloc(sizeof(TrieNode));
    if (trie->root == NULL) {
        free(trie);
        return NULL;
    }
    trie->root->valid = false;
    for (size_t i = 0; i < 128; ++i)
        trie->root->links[i] = NULL;
    return trie;
}
static TrieNode *trie_insert_node(TrieNode *root, const char *str)
{
    if (root == NULL) {
        root = (TrieNode*) malloc(sizeof(TrieNode));
        if (root == NULL)
            return NULL;
        root->valid = false;
        for (size_t i = 0; i < 128; ++i)
            root->links[i] = NULL;
    }
    if (*str == '\0')
        root->valid = true;
    else
        root->links[*str] = trie_insert_node(root->links[*str], str + 1);
    return root;
}
Trie *trie_create_from_strings(const char **strs, size_t size)
{
    Trie *trie = trie_create();
    if (trie == NULL)
        return NULL;
    for (size_t i = 0; i < size; ++i) {
        trie->root = trie_insert_node(trie->root, strs[i]);
    }
    return trie;
}
void trie_insert(Trie *trie, const char *str)
{
    trie->root = trie_insert_node(trie->root, str);
}
static bool trie_match(TrieNode *root, const char *str)
{
    if (root == NULL)
        return false;
    if (*str == '\0')
        return root->valid;
    return trie_match(root->links[*str], str + 1);
}
bool trie_find(Trie *trie, const char *str)
{
    return trie_match(trie->root, str);
}
static void trie_print_valids(TrieNode *root, char *pprefix, FILE *fp)
{
    if (root == NULL)
        return;
    if (root->valid)
        fprintf(fp, "%s\n", pprefix);
    size_t len = strlen(pprefix);
    char *nprefix = (char*) malloc((len + 2) * sizeof(char));
    if (nprefix == NULL)
        return;
    strncpy(nprefix, pprefix, len);
    nprefix[len + 1] = '\0';
    for (size_t i = 0; i < 128; ++i) {
        nprefix[len] = i;
        trie_print_valids(root->links[i], nprefix, fp);
    }
    free(nprefix);
}
void trie_print(Trie *trie, FILE *fp)
{
    trie_print_valids(trie->root, "", fp);
}
static void trie_free_nodes(TrieNode *root)
{
    if (root == NULL)
        return;
    for (size_t i = 0; i < 128; ++i) {
        trie_free_nodes(root->links[i]);
    }
    free(root);
}
void trie_destroy(Trie *trie)
{
    trie_free_nodes(trie->root);
    free(trie);
}
