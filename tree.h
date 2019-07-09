/**
 * \file tree.h
 *
 * This file contains the declarations of tree-related functions.
 * @author Zoltan Szatmary
 *
  */

#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *parent, *left, *right;
} TreeNode;

typedef struct Tree Tree;

/** Dynamically allocates a Tree (aka struct Tree). */
Tree *tree_create();
/** Inserts the given value into the tree, if it isn't already. */
void tree_insert(Tree *tree, int val);
/** Prints out the tree to the given out. */
void tree_print(Tree *tree, FILE *out);
/** Frees the nodes with calling 'free_nodes(TreeNode *root)' which is a recursive function. This has no effect on the struct itself. */
void tree_clear(Tree *tree);
/** Calls 'tree_clear(Tree *tree)' and frees the dynamically allocated struct. */
void tree_destroy(Tree *tree);

#endif /* TREE_H */
