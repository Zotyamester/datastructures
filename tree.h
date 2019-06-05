/**
 * \file tree.h
 *
 * This file contains the declarations of tree-related functions.
 * @author Zoltan Szatmary
 *
 **/

#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *parent, *left, *right;
} TreeNode;

typedef struct Tree Tree;

/**Dynamically allocates a Tree (aka struct Tree).**/
Tree *create_tree();
/**Inserts the given value into the tree, if it isn't already.**/
void insert_tree(Tree *tree, int val);
/**Prints out the tree to the given out.**/
void print_tree(Tree *tree, FILE *out);
/**Frees the nodes with calling 'free_nodes(TreeNode *root)' which is a recursive function. This has no effect on the struct itself.**/
void clear_tree(Tree *tree);
/**Calls 'clear_tree(Tree *tree)' and frees the dynamically allocated struct.**/
void delete_tree(Tree *tree);

#endif /* TREE_H */
