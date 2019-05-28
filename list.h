/**
 * \file list.h
 *
 * This file contains the declarations of list-related functions.
 * The list is a doubly-linked list.
 * @author Zoltan Szatmary
 *
 **/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*#include "debugmalloc.h"*/

typedef struct ListNode {
    int data;
    struct ListNode *prev, *next;
} ListNode;

typedef struct List List;

/**Dynamically allocates a List (aka struct List).**/
List *create_list();

/**Dynamically allocates a List (with 'create_list()') and initializes it with the given array.**/
List *create_list_from_array(int *array, size_t size);

/**Scans for a list of data in the given in and makes a list.**/
List *scan_list(FILE *fp);

/**Makes a deep copy of the given list.**/
List *copy_list(List *list);

/**Makes a sublist of the given list. The sublist will be a from left-closed, from right-open interval.**/
List *sublist(List *list, int from, int to);

/**Links a list to another.**/
void link_list(List *list, List *other);

/**Reverses the list.**/
void reverse_list(List *list);

/**Adds a new node to the head of the list.**/
void push_listfront(List *list, int data);

/**Adds a new node to the back of the list.**/
void push_listback(List *list, int data);

/**Retrieves and deletes the first value (if it exists) of the list.**/
int pop_listhead(List *list);

/**Retrieves and deletes the last value (if it exists) of the list.**/
int pop_listback(List *list);

/**Retrieves the first value (if it exists) of the list.**/
int get_listhead(List *list);

/**Retrieves the last value (if it exists) of the list.**/
int get_listback(List *list);

/**Inserts a node to the given position (index from 0) of the list.**/
void insert_list(List *list, int index, int data);

/**Returns the size of the list. It runs in O(1) since it always keeps track of the size.**/
size_t get_listsize(List *list);

/**Returns with a bool indicating whether the list is empty or not.**/
bool isempty_list(List *list);

/**Returns an 'iterator' (ListNode*).**/
ListNode *get_listbegin(List *list);

/**Returns with NULL which is basically the end of the list.**/
inline ListNode *get_listend()
{
    return NULL;
}

/**Steps one with the iterator. Returns with the next element in the list.**/
ListNode *get_listnext(ListNode *node);

/**Prints the list to the give out separated by spaces (without an ending '\n').**/
void print_list(List *list, FILE *fp);

/**Gets the item form the given position (index from 0 to the (size - 1)th) of the list.**/
int get_listindex(List *list, int index);

/**Allocates an array based on the elements of the list.**/
size_t list_to_array(int **array_ptr, List *list);

/**Compares two nodes in the 'standard way': a < b = -1   a == b = 0   a > b = 1**/
int cmp_listnodes(ListNode *a, ListNode *b);

/**Removes and frees the given node.**/
void remove_listnode(List *list, ListNode *node);

/**Searches for the specified value and if it finds then removes it.**/
void remove_listitem(List *list, int data);

/**Frees the nodes in the list and resets size.**/
void clear_list(List *list);

/**Calls 'clear_list(List *list)' and frees the dynamically allocated struct.**/
void delete_list(List *list);


#endif /* LIST_H */
