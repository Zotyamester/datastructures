/**
 * \file list.c
 *
 * This file defines the declarations and struct List from 'list.h'.
 * @author Zoltan Szatmary
 *
 */

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

List *list_create_with_size(size_t size)
{
    List *list = list_create();
    if (list == NULL)
        return NULL;
    if (size == 0)
        return list;
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    if (node == NULL) {
        free(list);
        return NULL;
    }
    node->data = 0;
    node->prev = node->next = NULL;
    list->head = list->tail = node;
    for (size_t i = 1; i < size; ++i) {
        node = (ListNode *) malloc(sizeof(ListNode));
        if (node == NULL) {
            list_destroy(list);
            return NULL;
        }
        node->data = NULL;
        node->prev = list->tail;
        list->tail->next = node;
        node->next = NULL;
        list->tail = node;
    }
    list->size = size;
    return list;
}

List *list_create_from_array(void **array, size_t size)
{
    List *list = list_create();
    if (list == NULL)
        return NULL;
    if (size == 0)
        return list;
    ListNode *root = (ListNode *) malloc(sizeof(ListNode));
    if (root == NULL)
        return list;
    root->data = array[0];
    root->prev = root->next = NULL;
    list->head = list->tail = root;
    ListNode *moving = root;
    for (size_t i = 1; i < size; ++i) {
        ListNode *node = (ListNode *) malloc(sizeof(ListNode));
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

List *list_scan(FILE *fp, void *(*scanner)(FILE *))
{
    List *list = (List *) malloc(sizeof(List));
    if (list == NULL)
        return NULL;
    void *temp;
    if ((temp = scanner(fp)) == NULL) {
        list->head = list->tail = NULL;
        list->size = 0;
        return list;
    }
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    if (node == NULL)
        return list;
    node->data = temp;
    node->prev = node->next = NULL;
    list->head = list->tail = node;
    list->size = 1;
    ListNode *moving = node;
    while ((temp = scanner(fp)) != NULL) {
        node = (ListNode *) malloc(sizeof(ListNode));
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
    ListNode *new_node = (ListNode *) malloc(sizeof(ListNode));
    copy->head = copy->tail = new_node;
    if (new_node == NULL)
        return copy;
    new_node->data = list->head->data;
    new_node->prev = new_node->next = NULL;
    copy->size = 1;
    ListNode *lmoving=list->head->next, *cmoving=new_node;
    while (lmoving != NULL) {
        ListNode *new_node = (ListNode *) malloc(sizeof(ListNode));
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

List *list_sub(List *list, size_t from, size_t to)
{
    List *new_list = list_create();
    if (new_list == NULL)
        return NULL;
    if (list->head == NULL)
        return new_list;
    ListNode *lhead = list->head;
    for (size_t i = 0; i < from; ++i, lhead = lhead->next);
    ListNode *root = (ListNode *) malloc(sizeof(ListNode));
    if (root == NULL)
        return new_list;
    root->data = lhead->data;
    root->prev = root->next = NULL;
    new_list->head = root;
    ListNode *moving = lhead->next, *new_moving = root;
    for (size_t i = from + 1; i < to; ++i, moving = moving->next) {
        ListNode *node = (ListNode *) malloc(sizeof(ListNode));
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

void list_cat(List *list, List *other)
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
        moving = moving->prev; /* Actually this is the next...  */
    }
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

void list_push_front(List *list, void *data)
{
    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
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

void list_push_back(List *list, void *data)
{
    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
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

void list_pop_front(List *list)
{
    ListNode *head = list->head;
    if (head->next != NULL)
        head->next->prev = NULL;
    else
        list->tail = NULL;
    list->head = head->next;
    --list->size;
    free(head);
}

void list_pop_back(List *list)
{
    ListNode *tail = list->tail;
    if (tail->prev != NULL)
        tail->prev->next = NULL;
    else
        list->head = NULL;
    list->tail = tail->prev;
    --list->size;
    free(tail);
}

void *list_front(List *list)
{
    return list->head->data;
}

void *list_back(List *list)
{
    return list->tail->data;
}

void list_insert(List *list, size_t index, void *data)
{
    if (index == 0) {
        list_push_front(list, data);
    } else {
        size_t i = 0;
        ListNode *moving = list->head;
        while (moving != NULL && i < index) {
            moving = moving->next;
            ++i;
        }
        ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
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

size_t list_size(List *list)
{
    return list->size;
}

bool list_empty(List *list)
{
    return list->size == 0;
}

ListNode *list_begin(List *list)
{
    return list->head;
}

void list_print(List *list, FILE *fp, void (*printer)(FILE *, void *))
{
    for (ListNode *moving = list->head; moving != NULL; moving = moving->next) {
        printer(fp, moving->data);
        putc(' ', fp);
    }
}

/** Indexing starts from 0 to the "list's size - 1"th element. */
void **list_get(List *list, size_t index)
{
    size_t i = 0;
    ListNode *moving = list->head;
    while (moving != NULL && i < index) {
        moving = moving->next;
        ++i;
    }
    return &moving->data;
}

size_t list_to_array(List *list, void ***array_ptr)
{
    void **array = (void **) malloc(list->size * sizeof(void *));
    if (array == NULL) {
        *array_ptr = NULL;
        return 0;
    }
    size_t i = 0;
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

void list_remove_item(List *list, void *data)
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

void list_free_data(List *list)
{
    for (ListNode *moving = list->head; moving != NULL; moving = moving->next) {
        free(moving->data);
        moving->data = NULL;
    }
}

void list_clear(List *list)
{
    ListNode *moving = list->head, *next;
    while (moving != NULL) {
        next = moving->next;
        free(moving);
        moving = next;
    }
    list->head = list->tail = NULL;
    list->size = 0;
}

void list_destroy(List *list)
{
    list_clear(list);
    free(list);
}
