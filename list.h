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

typedef struct ListNode {
    int data;
    struct ListNode *prev, *next;
} ListNode;

typedef struct List List;

/**Dynamically allocates a List (aka struct List).**/
List *list_create();

/**Dynamically allocates a List (with 'list_create()') and initializes it with the given array.**/
List *list_create_from_array(int *array, size_t size);

/**Scans for a list of data in the given in and makes a list.**/
List *list_scan(FILE *fp);

/**Makes a deep copy of the given list.**/
List *list_copy(List *list);

/**Makes a sublist of the given list. The sublist will be a from left-closed, from right-open interval.**/
List *list_sub(List *list, size_t from, size_t to);

/**Links a list to another.**/
void list_link(List *list, List *other);

/**Reverses the list.**/
void list_reverse(List *list);

/**Adds a new node to the head of the list.**/
void list_push_front(List *list, int data);

/**Adds a new node to the back of the list.**/
void list_push_back(List *list, int data);

/**Deletes the first value (if it exists) of the list.**/
void list_pop_front(List *list);

/**Deletes the last value (if it exists) of the list.**/
void list_pop_back(List *list);

/**Retrieves the first value (if it exists) of the list.**/
int list_get_front(List *list);

/**Retrieves the last value (if it exists) of the list.**/
int list_get_back(List *list);

/**Inserts a node to the given position (index from 0) of the list.**/
void list_insert(List *list, size_t index, int data);

/**Returns the size of the list. It runs in O(1) since it always keeps track of the size.**/
size_t list_get_size(List *list);

/**Returns with a bool indicating whether the list is empty or not.**/
bool list_is_empty(List *list);

/**Returns an 'iterator' (ListNode*).**/
ListNode *list_get_begin(List *list);

/**Returns with NULL which is basically the end of the list.**/
inline ListNode *list_get_end()
{
    return NULL;
}

/**Steps one with the iterator. Returns with the next element in the list.**/
ListNode *list_get_next(ListNode *node);

/**Prints the list to the give out separated by spaces (without an ending '\n').**/
void list_print(List *list, FILE *fp);

/**Gets the (pointer to it) item form the given position (index from 0 to the (size - 1)th) of the list.**/
int *list_get_index(List *list, size_t index);

/**Allocates an array based on the elements of the list.**/
size_t list_to_array(int **array_ptr, List *list);

/**Removes and frees the given node.**/
void list_remove_node(List *list, ListNode *node);

/**Searches for the specified value and if it finds then removes it.**/
void list_remove_item(List *list, int data);

/**Frees the nodes in the list and resets size.**/
void list_clear(List *list);

/**Calls 'list_clear(List *list)' and frees the dynamically allocated struct.**/
void list_delete(List *list);


#endif /* LIST_H */
