#include "tree.h"

struct Tree {
    TreeNode *root;
};

Tree *create_tree() {
    Tree *tree = (Tree*) malloc(sizeof(Tree));
    if(tree == NULL) return NULL;
    tree->root = NULL;
    return tree;
}

static TreeNode *insert_node(TreeNode *root, TreeNode *parent, int val) {
    if(root == NULL) {
        root = (TreeNode*) malloc(sizeof(TreeNode));
        if(root == NULL) return NULL;
        root->parent = parent;
        root->left = root->right = NULL;
        root->val = val;
    } else {
        if(val < root->val) {
            root->left = insert_node(root->left, root, val);
        } else if(val > root->val) {
            root->right = insert_node(root->right, root, val);
        }
    }
    return root;
}

void insert_tree(Tree *tree, int val) {
    tree->root = insert_node(tree->root, NULL, val);
}

static void print_nodes(TreeNode *root, FILE *out) {
    if(root == NULL) return;

    print_nodes(root->left, out);
    fprintf(out, "%d ", root->val);
    print_nodes(root->right, out);
}

void print_tree(Tree *tree, FILE *out) {
    print_nodes(tree->root, out);
}

static void free_nodes(TreeNode *root) {
    if (root == NULL)
        return;

    free_nodes(root->left);
    free_nodes(root->right);
    free(root);
}

void clear_tree(Tree *tree) {
    free_nodes(tree->root);
    tree->root = NULL;
}

void delete_tree(Tree *tree) {
    clear_tree(tree);
    free(tree);
}
