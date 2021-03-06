/**
 * \file list.h
 *
 * This file contains the declarations of list-related functions.
 * The list is a doubly-linked list.
 * @author Zoltan Szatmary
 *
 */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode {
    void *data;
    struct ListNode *prev, *next;
} ListNode;

typedef struct List List;

/** Dynamically allocates a List. */
List *list_create();

/** Creates a list with 'size' zeros. */
List *list_create_with_size(size_t size);

/** Dynamically allocates a List and initializes it with the given array. */
List *list_create_from_array(void **array, size_t size);

/** Scans for a list of data in the given in and makes a list. */
List *list_scan(FILE *fp, void *(*scanner)(FILE *));

/** Makes a deep copy of the given list. */
List *list_copy(List *list);

/** Makes a sublist of the given list. The sublist will be a from left-closed, from right-open interval. */
List *list_sub(List *list, size_t from, size_t to);

/** Links a list to another. */
void list_cat(List *list, List *other);

/** Returns the size of the list. It runs in O(1) since it always keeps track of the size. */
size_t list_size(List *list);

/** Returns with a bool indicating whether the list is empty or not. */
bool list_empty(List *list);

/** Reverses the list. */
void list_reverse(List *list);

/** Inserts a node to the given position (index from 0) of the list. */
void list_insert(List *list, size_t index, void *data);

/** Adds a new node to the head of the list. */
void list_push_front(List *list, void *data);

/** Adds a new node to the back of the list. */
void list_push_back(List *list, void *data);

/** Deletes the first value of the list. */
void list_pop_front(List *list);

/** Deletes the last value of the list. */
void list_pop_back(List *list);

/** Retrieves the first value of the list. */
void *list_front(List *list);

/** Retrieves the last value of the list. */
void *list_back(List *list);

/** Gets the (pointer to it) item form the given position (index from 0 to the (size - 1)th) of the list. */
void **list_get(List *list, size_t index);

/** Returns an 'iterator' (ListNode*). */
ListNode *list_begin(List *list);

/** Returns with NULL which is basically the end of the list. */
inline ListNode *list_end(List *list)
{
    return NULL;
}

/** Steps one with the iterator. Returns with the next element in the list. */
inline ListNode *list_next(ListNode *node)
{
    return node->next;
}

/** Prints the list to the give out separated by spaces (without an ending '\n'). */
void list_print(List *list, FILE *fp, void (*printer)(FILE *, void *));

/** Allocates an array based on the elements of the list. */
size_t list_to_array(List *list, void ***array_ptr);

/** Removes and frees the given node. */
void list_remove_node(List *list, ListNode *node);

/** Searches for the specified value and if it finds then removes it. */
void list_remove_item(List *list, void *data);

/**
 * Calls 'free()' for each 'void *' that is stored in the nodes's data field and then zeroes it out.
 * Warnings:
 *   - It doesn't work if not all of the pointers point to dynamically allocated memory.
 *   - It doesn't free the nodes themselves, just the data.
 */
void list_free_data(List *list);

/** Frees the nodes in the list and resets size. */
void list_clear(List *list);

/** Clears the nodes and frees the dynamically allocated struct. */
void list_destroy(List *list);


#endif /* LIST_H */
