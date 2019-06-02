#include "trie.h"
#include <stdio.h>

typedef struct TrieNode {
    struct {
        bool is_valid;
        struct TrieNode *link;
    } data[26];
} TrieNode;

struct Trie {
    TrieNode *root;
};

Trie *trie_create()
{
    Trie *trie = (Trie*) malloc(sizeof(Trie));
    if (trie == NULL)
        return NULL;
    trie->root = NULL;
    return trie;
}
static TrieNode *trie_insert_node(TrieNode *node, const char *str)
{
    if (*str == '\0') return node;
    int index = (*str) - 'A';
    if (node == NULL) {
        node = (TrieNode*) malloc(sizeof(TrieNode));
        if (node == NULL)
            return NULL;
        for (int i = 0; i < 26; ++i) {
            node->data[i].link = NULL;
            if (i == index) {
                if (str[1] == '\0') {
                    node->data[i].is_valid = true;
                } else {
                    node->data[i].is_valid = false;
                    node->data[i].link = trie_insert_node(node->data[i].link, str + 1);
                }
            } else {
                node->data[i].is_valid = false;
            }
        }
        return node;
    } else {
        if (str[1] == '\0')
            node->data[index].is_valid = true;
        else
            node->data[index].link = trie_insert_node(node->data[index].link,  str + 1);
        return node;
    }
}
Trie *trie_create_from_strings(const char **strs, size_t size)
{
    Trie *trie = trie_create();
    if (trie == NULL)
        return NULL;
    for (int i = 0; i < size; ++i) {
        trie_insert_node(trie->root, strs[i]);
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
        return *str == '\0';
    if (*str == '\0')
        return false;

    int index = (*str) - 'A';

    if (str[1] == '\0') {
        if (root->data[index].is_valid)
            return true;
    } else {
        return trie_match(root->data[index].link, str + 1);
    }
}
bool trie_search(Trie *trie, const char *str)
{
    return trie_match(trie->root, str);
}
static void trie_free_nodes(TrieNode *root)
{
    if (root == NULL)
        return NULL;
    for (int i = 0; i < 26; ++i) {
        trie_free_nodes(root->data[i].link);
    }
    free(root);
}
void trie_delete(Trie *trie)
{
    trie_free_nodes(trie->root);
    free(trie);
}
