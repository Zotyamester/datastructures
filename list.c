/**
 * \file list.c
 *
 * This file defines the declarations and struct List from 'list.h'.
 * @author Zoltan Szatmary
 *
 **/

#include "list.h"

struct List {
    ListNode *start, *end;
    size_t size;
};

List *create_list() {
    List *list = (List*) malloc(sizeof(List));
    if(list == NULL) return NULL;
    list->start = list->end = NULL;
    list->size = 0;
    return list;
}

List *create_list_from_array(int *array, size_t size) {
    List *list = create_list();
    if(list == NULL) return NULL;
    if(size == 0) return list;
    ListNode *root = (ListNode*) malloc(sizeof(ListNode));
    if(root == NULL) return list;
    root->data = array[0];
    root->prev = root->next = NULL;
    list->start = list->end = root;
    ListNode *moving = root;
    for(int i = 1; i < size; ++i) {
        ListNode *node = (ListNode*) malloc(sizeof(ListNode));
        if(node == NULL) {
            list->end = moving;
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

List *scan_list(FILE *fp) {
    List *list = create_list();
    if(list == NULL) return NULL;
    int temp;
    if(fscanf(fp, "%d", &temp) < 1) return list;
    ListNode *node = (ListNode*) malloc(sizeof(ListNode));
    if(node == NULL) return list;
    node->data = temp;
    node->prev = node->next = NULL;
    list->start = list->end = node;
    list->size = 1;
    ListNode *moving = node;
    while(fscanf(fp, "%d", &temp) == 1) {
        node = (ListNode*) malloc(sizeof(ListNode));
        if(node == NULL) {
            list->end = moving;
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

List *copy_list(List *list) {
    List *copy = (List*) malloc(sizeof(List));
    if(copy == NULL) return NULL;
    if(list->size == 0) {
        copy->start = copy->end = NULL;
        copy->size = 0;
        return copy;
    }
    copy->size = 0;
    ListNode *new_node = (ListNode*) malloc(sizeof(ListNode));
    copy->start = copy->end = new_node;
    if(new_node == NULL) return copy;
    new_node->data = list->start->data;
    new_node->prev = new_node->next = NULL;
    copy->size = 1;
    ListNode *lmoving=list->start->next, *cmoving=new_node;
    while(lmoving != NULL) {
        ListNode *new_node = (ListNode*) malloc(sizeof(ListNode));
        if(new_node == NULL) {
            copy->end = cmoving;
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
    copy->end = cmoving;
    return copy;
}

List *sublist(List *list, int from, int to) {
    List *new_list = create_list();
    if(new_list == NULL) return NULL;
    if(list->start == NULL) return new_list;
    ListNode *lstart = list->start;
    for(int i = 0; i < from; ++i, lstart = lstart->next);
    ListNode *root = (ListNode*) malloc(sizeof(ListNode));
    if(root == NULL) return new_list;
    root->data = lstart->data;
    root->prev = root->next = NULL;
    new_list->start = root;
    ListNode *moving = lstart->next, *new_moving = root;
    for(int i = from + 1; i < to; ++i, moving = moving->next) {
        ListNode *node = (ListNode*) malloc(sizeof(ListNode));
        if(node == NULL) {
            new_list->size = i - from;
            return new_list;
        }
        node->data = moving->data;
        node->prev = new_moving;
        node->next = NULL;
        new_moving->next = node;
        new_list->end = node;
        new_moving = node;
    }
    new_list->size = to - from;
    return new_list;
}

void add_list(List *list, List *other) {
    List *othercopy = copy_list(other);
    if(othercopy == NULL) return;
    list->size += othercopy->size;
    if(list->end == NULL)
        list->start = othercopy->start;
    else
        list->end->next = othercopy->start;
    if(othercopy->start != NULL) {
        list->start->prev = list->end;
        list->end = othercopy->end;
    }
    free(othercopy);
}

void reverse_list(List *list) {
    ListNode *moving = list->start, *temp;
    while(moving != NULL) {
        temp = moving->prev;
        moving->prev = moving->next;
        moving->next = temp;
        moving = moving->prev; /* Actually this is the next... */
    }
    temp = list->start;
    list->start = list->end;
    list->end = temp;
}

void add_listhead(List *list, int data) {
    ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = list->start;
    if(list->start != NULL) list->start->prev = newNode;
    list->start = newNode;
    if(list->end == NULL) list->end = newNode;
    ++list->size;
}

void add_listback(List *list, int data) {
    ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->prev = list->end;
    newNode->next = NULL;
    if(list->end == NULL) {
        list->start = list->end = newNode;
    } else {
        list->end->next = newNode;
        list->end = newNode;
    }
    ++list->size;
}

int pop_listhead(List *list) {
    ListNode *start = list->start;
    if(start->next != NULL) start->next->prev = NULL;
    else list->end = NULL;
    list->start = start->next;
    --list->size;
    int data = start->data;
    free(start);
    return data;
}

int pop_listback(List *list) {
    ListNode *end = list->end;
    if(end->prev != NULL) end->prev->next = NULL;
    else list->start = NULL;
    list->end = end->prev;
    --list->size;
    int data = end->data;
    free(end);
    return data;
}

int get_listhead(List *list) {
    return list->start->data;
}

int get_listback(List *list) {
    return list->end->data;
}

void insert_list(List *list, int index, int data) {
    if(index == 0) {
        add_listhead(list, data);
    } else {
        int i = 0;
        ListNode *moving = list->start;
        while(moving != NULL && i < index) {moving = moving->next; ++i;}
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        if(newNode == NULL) return;
        newNode->data = data;
        newNode->prev = moving->prev;
        moving->prev->next = newNode;
        moving->prev = newNode;
        newNode->next = moving;
        newNode->data = data;
        ++list->size;
    }
}

size_t get_listsize(List *list) {
    return list->size;
}

bool isempty_list(List *list) {
    return list->size == 0;
}

ListNode *get_listbegin(List *list) {
    return list->start;
}

ListNode *get_listend() {
    return NULL;
}

ListNode *get_listnext(ListNode *node) {
    return node->next;
}

void print_list(List *list, FILE *fp) {
    for(ListNode *moving = list->start; moving != NULL; moving = moving->next)
        fprintf(fp, "%d ", moving->data);
    putchar('\n');
}

int get_listitem(List *list, int index) {
    int i = 0;
    ListNode *moving = list->start;
    while(moving != NULL && i < index) {moving=moving->next;++i;}
    return moving->data;
}

size_t list_to_array(int **array_ptr, List *list) {
    int *array = (int*) malloc(list->size*sizeof(int));
    if(array == NULL) {
        *array_ptr = NULL;
        return 0;
    }
    int i = 0;
    ListNode *moving = list->start;
    while(moving != NULL) {
        array[i++] = moving->data;
        moving = moving->next;
    }
    *array_ptr = array;
    return list->size;
}

int cmp_listnodes(ListNode *a, ListNode *b) {
    if(a->data < b->data) return -1;
    return a->data > b->data;
}

void remove_listnode(List *list, ListNode *node) {
    if(node->prev != NULL) node->prev->next = node->next;
    else list->start = node->next;
    if(node->next != NULL) node->next->prev = node->prev;
    else list->end = node->prev;
    free(node);
    --list->size;
}

void remove_listitem(List *list, int data) {
    if(list->start == NULL) return;
    ListNode *moving = list->start;
    while(moving != NULL && moving->data != data) moving = moving->next;
    if(moving->data != data) return;
    remove_listnode(list, moving);
}

void clear_list(List *list) {
    ListNode *moving=list->start, *next;
    while(moving != NULL) {
        next = moving->next;
        free(moving);
        moving = next;
    }
    list->start = list->end = NULL;
    list->size = 0;
}

void delete_list(List *list) {
    clear_list(list);
    free(list);
    list = NULL;
}
