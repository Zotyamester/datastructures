/**
 * \file list.c
 *
 * This file defines the declarations and struct List from 'list.h'.
 * @author Zoltan Szatmary
 *
 **/

#include "list.h"

struct List {
    ListNode *head, *tail;
    size_t size;
};

List *list_create()
{
    List *list = (List*) malloc(sizeof(List));
    if (list == NULL)
        return NULL;
    list->head = list->tail = NULL;
    list->size = 0;
    return list;
}

List *list_create_from_array(int *array, size_t size)
{
    List *list = list_create();
    if (list == NULL)
        return NULL;
    if (size == 0)
        return list;
    ListNode *root = (ListNode*) malloc(sizeof(ListNode));
    if (root == NULL)
        return list;
    root->data = array[0];
    root->prev = root->next = NULL;
    list->head = list->tail = root;
    ListNode *moving = root;
    for (int i = 1; i < size; ++i) {
        ListNode *node = (ListNode*) malloc(sizeof(ListNode));
        if (node == NULL) {
            list->tail = moving;
            list->size = i;
            return list;
        }
        node->data = array[i];
        node->prev = moving;
        node->next = NULL;
        moving->next = node;
        moving = node;
    }
    list->size = size;
    return list;
}

List *list_scan(FILE *fp)
{
    List *list = list_create();
    if (list == NULL)
        return NULL;
    int temp;
    if (fscanf(fp, "%d", &temp) < 1) return list;
    ListNode *node = (ListNode*) malloc(sizeof(ListNode));
    if (node == NULL)
        return list;
    node->data = temp;
    node->prev = node->next = NULL;
    list->head = list->tail = node;
    list->size = 1;
    ListNode *moving = node;
    while (fscanf(fp, "%d", &temp) == 1) {
        node = (ListNode*) malloc(sizeof(ListNode));
        if (node == NULL) {
            list->tail = moving;
            return list;
        }
        node->data = temp;
        node->prev = moving;
        node->next = NULL;
        ++list->size;
        moving->next = node;
        moving = node;
    }
    return list;
}

List *list_copy(List *list)
{
    List *copy = (List*) malloc(sizeof(List));
    if (copy == NULL)
        return NULL;
    if (list->size == 0) {
        copy->head = copy->tail = NULL;
        copy->size = 0;
        return copy;
    }
    copy->size = 0;
    ListNode *new_node = (ListNode*) malloc(sizeof(ListNode));
    copy->head = copy->tail = new_node;
    if (new_node == NULL)
        return copy;
    new_node->data = list->head->data;
    new_node->prev = new_node->next = NULL;
    copy->size = 1;
    ListNode *lmoving=list->head->next, *cmoving=new_node;
    while (lmoving != NULL) {
        ListNode *new_node = (ListNode*) malloc(sizeof(ListNode));
        if (new_node == NULL) {
            copy->tail = cmoving;
            return copy;
        }
        new_node->data = lmoving->data;
        new_node->prev = cmoving;
        cmoving->next = new_node;
        new_node->next = NULL;
        lmoving = lmoving->next;
        cmoving = new_node;
        ++copy->size;
    }
    copy->tail = cmoving;
    return copy;
}

List *list_sub(List *list, int from, int to)
{
    List *new_list = list_create();
    if (new_list == NULL)
        return NULL;
    if (list->head == NULL)
        return new_list;
    ListNode *lhead = list->head;
    for (int i = 0; i < from; ++i, lhead = lhead->next);
    ListNode *root = (ListNode*) malloc(sizeof(ListNode));
    if (root == NULL)
        return new_list;
    root->data = lhead->data;
    root->prev = root->next = NULL;
    new_list->head = root;
    ListNode *moving = lhead->next, *new_moving = root;
    for (int i = from + 1; i < to; ++i, moving = moving->next) {
        ListNode *node = (ListNode*) malloc(sizeof(ListNode));
        if (node == NULL) {
            new_list->size = i - from;
            return new_list;
        }
        node->data = moving->data;
        node->prev = new_moving;
        node->next = NULL;
        new_moving->next = node;
        new_list->tail = node;
        new_moving = node;
    }
    new_list->size = to - from;
    return new_list;
}

void list_link(List *list, List *other)
{
    List *othercopy = list_copy(other);
    if (othercopy == NULL)
        return;
    list->size += othercopy->size;
    if (list->tail == NULL)
        list->head = othercopy->head;
    else
        list->tail->next = othercopy->head;
    if (othercopy->head != NULL) {
        list->head->prev = list->tail;
        list->tail = othercopy->tail;
    }
    free(othercopy);
}

void list_reverse(List *list)
{
    ListNode *moving = list->head, *temp;
    while (moving != NULL) {
        temp = moving->prev;
        moving->prev = moving->next;
        moving->next = temp;
        moving = moving->prev; /* Actually this is the next... */
    }
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

void list_push_front(List *list, int data)
{
    ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = list->head;
    if (list->head != NULL)
        list->head->prev = newNode;
    list->head = newNode;
    if (list->tail == NULL)
        list->tail = newNode;
    ++list->size;
}

void list_push_back(List *list, int data)
{
    ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->prev = list->tail;
    newNode->next = NULL;
    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    ++list->size;
}

int list_pop_front(List *list)
{
    ListNode *head = list->head;
    if (head->next != NULL)
        head->next->prev = NULL;
    else
        list->tail = NULL;
    list->head = head->next;
    --list->size;
    int data = head->data;
    free(head);
    return data;
}

int list_pop_back(List *list)
{
    ListNode *tail = list->tail;
    if (tail->prev != NULL)
        tail->prev->next = NULL;
    else
        list->head = NULL;
    list->tail = tail->prev;
    --list->size;
    int data = tail->data;
    free(tail);
    return data;
}

int list_get_front(List *list)
{
    return list->head->data;
}

int list_get_back(List *list)
{
    return list->tail->data;
}

void list_insert(List *list, int index, int data)
{
    if (index == 0) {
        list_push_front(list, data);
    } else {
        int i = 0;
        ListNode *moving = list->head;
        while (moving != NULL && i < index) {
            moving = moving->next;
            ++i;
        }
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        if (newNode == NULL)
            return;
        newNode->data = data;
        newNode->prev = moving->prev;
        moving->prev->next = newNode;
        moving->prev = newNode;
        newNode->next = moving;
        newNode->data = data;
        ++list->size;
    }
}

size_t list_get_size(List *list)
{
    return list->size;
}

bool list_is_empty(List *list)
{
    return list->size == 0;
}

ListNode *list_get_begin(List *list)
{
    return list->head;
}

ListNode *list_get_next(ListNode *node)
{
    return node->next;
}

void list_print(List *list, FILE *fp)
{
    for (ListNode *moving = list->head; moving != NULL; moving = moving->next)
        fprintf(fp, "%d ", moving->data);
}

/** Indexing starts from 0 to the "list's size - 1"th element. **/
int *list_get_index(List *list, int index)
{
    int i = 0;
    ListNode *moving = list->head;
    while (moving != NULL && i < index) {
        moving = moving->next;
        ++i;
    }
    return &moving->data;
}

size_t list_to_array(int **array_ptr, List *list)
{
    int *array = (int*) malloc(list->size*sizeof(int));
    if (array == NULL) {
        *array_ptr = NULL;
        return 0;
    }
    int i = 0;
    ListNode *moving = list->head;
    while (moving != NULL) {
        array[i++] = moving->data;
        moving = moving->next;
    }
    *array_ptr = array;
    return list->size;
}

void list_remove_node(List *list, ListNode *node)
{
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        list->head = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;
    free(node);
    --list->size;
}

void list_remove_item(List *list, int data)
{
    if (list->head == NULL)
        return;
    ListNode *moving = list->head;
    while (moving != NULL && moving->data != data)
        moving = moving->next;
    if (moving->data != data)
        return;
    list_remove_node(list, moving);
}

void list_clear(List *list)
{
    ListNode *moving=list->head, *next;
    while (moving != NULL) {
        next = moving->next;
        free(moving);
        moving = next;
    }
    list->head = list->tail = NULL;
    list->size = 0;
}

void list_delete(List *list)
{
    list_clear(list);
    free(list);
    list = NULL;
}
