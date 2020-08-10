/**
 * \file list.c
 *
 * This file defines the declarations and struct Tree from 'tree.h'.
 * @author Zoltan Szatmary
 *
 */

#include "tree.h"

struct Tree {
    TreeNode *root;
};

Tree *tree_create() {
    Tree *tree = (Tree*) malloc(sizeof(Tree));
    if(tree == NULL) return NULL;
    tree->root = NULL;
    return tree;
}

static TreeNode *tree_insert_node(TreeNode *root, TreeNode *parent, int val) {
    if(root == NULL) {
        root = (TreeNode*) malloc(sizeof(TreeNode));
        if(root == NULL) return NULL;
        root->parent = parent;
        root->left = root->right = NULL;
        root->val = val;
    } else {
        if(val < root->val) {
            root->left = tree_insert_node(root->left, root, val);
        } else if(val > root->val) {
            root->right = tree_insert_node(root->right, root, val);
        }
    }
    return root;
}

void tree_insert(Tree *tree, int val) {
    tree->root = tree_insert_node(tree->root, NULL, val);
}

static TreeNode *tree_find_node(TreeNode *root, int val)
{
    if (root == NULL)
        return NULL;
    if (root->val == val)
        return root;
    TreeNode *node = NULL;
    if ((node = tree_find_node(root->left, val)) != NULL)
        return node;
    return tree_find_node(root->right, val);
}

TreeNode *tree_find(Tree *tree, int val)
{
    return tree_find_node(tree->root, val);
}

static void tree_print_nodes(TreeNode *root, FILE *out) {
    if(root == NULL) return;

    tree_print_nodes(root->left, out);
    fprintf(out, "%d ", root->val);
    tree_print_nodes(root->right, out);
}

void tree_print(Tree *tree, FILE *out) {
    tree_print_nodes(tree->root, out);
}

static void tree_free_nodes(TreeNode *root) {
    if (root == NULL)
        return;

    tree_free_nodes(root->left);
    tree_free_nodes(root->right);
    free(root);
}

void tree_clear(Tree *tree) {
    tree_free_nodes(tree->root);
    tree->root = NULL;
}

void tree_destroy(Tree *tree) {
    tree_clear(tree);
    free(tree);
}
