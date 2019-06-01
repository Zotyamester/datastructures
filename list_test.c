#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"

/** Test cases **/

#define CREATE_LIST_TEMPLATE()                  \
            do {                                \
                list = list_create();           \
                if (list == NULL)               \
                    return false;               \
                for (int i = 1; i <= 5; ++i)    \
                    list_push_back(list, i);     \
            } while(0)

/** Creating and printing **/
bool list_testcase1()
{
    printf("---TEST 1.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    /** Same as --> list_print(list, stdout); **/
    for (ListNode *iter = list_get_begin(list); iter != list_get_end(); iter = list_get_next(iter)) {
        printf("%d ", iter->data);
    }
    putchar('\n');
    list_print(list, stdout);

    list_delete(list);
    return true;
}

/** Copying and reversing **/
bool list_testcase2()
{
    printf("---TEST 2.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    List *copy = list_copy(list);
    if (copy == NULL)
        return false;

    list_reverse(copy);

    printf("List:");
    list_print(list, stdout);
    printf("\nCopied list:");
    list_print(copy, stdout);
    putchar('\n');

    list_delete(list);
    list_delete(copy);
    return true;
}

/** Retrieving elements **/
bool list_testcase3()
{
    printf("---TEST 3.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    printf("%d\n", list_get_index(list, 0));
    printf("%d\n", list_get_index(list, 3));
    printf("%d\n", list_get_index(list, 1));
    printf("%d\n", list_get_index(list, 4));

    list_delete(list);
    return true;
}

/** Popping from back and front **/
bool list_testcase4()
{
    printf("---TEST 4.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    printf("%d\n", list_pop_front(list));
    printf("%d\n", list_pop_front(list));
    printf("%d\n", list_pop_back(list));
    printf("%d\n", list_pop_back(list));

    list_delete(list);
    return true;
}

bool list_testcase5()
{
    printf("---TEST 5.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    list_remove_item(list, 1);
    list_remove_item(list, 3);
    list_remove_item(list, 5);
    list_print(list, stdout);
    putchar('\n');

    list_delete(list);
    return true;
}

/** Creating from array **/
bool list_testcase6()
{
    printf("---TEST 6.---\n");
    int array[5] = {1, 2, 3, 4, 5};
    List *list = list_create_from_array(array, 5);
    if (list == NULL)
        return false;

    printf("Array:");
    for (int i = 0; i < 5; ++i)
        printf("%d ", array[i]);

    printf("\nList:");
    list_print(list, stdout);
    putchar('\n');

    list_delete(list);
    return true;
}

/** Scanning from input **/
bool list_testcase7()
{
    printf("---TEST 7.---\nEnter the values:");
    List *list = list_scan(stdin);
    if (list == NULL)
        return false;

    list_print(list, stdout);
    putchar('\n');
    return true;
}

/** Iterators **/
bool list_testcase8()
{
    printf("---TEST 8.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    for (ListNode *iter = list_get_begin(list); iter != list_get_end(); iter = list_get_next(iter)) {
        printf("iter->data = %d\n", iter->data);
    }

    list_delete(list);
    return true;
}

/** Link lists together **/
bool list_testcase9()
{
    printf("---TEST 9.---\n");
    List *list = list_create(), *list2 = list_create();
    if (list == NULL) {
        if (list2 != NULL)
            list_delete(list2);
        return false;
    } else if (list2 == NULL) {
        list_delete(list);
        return false;
    }
    for (int i = 1; i <= 5; ++i)
        list_push_back(list, i);
    for (int i = 6; i <= 10; ++i)
        list_push_back(list2, i);

    list_link(list, list2);

    list_print(list, stdout);
    putchar('\n');

    list_delete(list);
    list_delete(list2);
    return true;
}

/** General test **/
bool list_testcase10()
{
    printf("---TEST 10.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    ListNode *a = list_get_begin(list);
    ListNode *b = list_get_next(a);
    int cmp = list_cmp_nodes(a, b);
    printf("Comparison --> %d %c %d\n", a->data, ((cmp == -1) ? '<' : ((cmp == 0) ? '=' : '>')), b->data);
    list_remove_node(list, a);

    printf("List:");
    list_print(list, stdout);
    int *array = NULL;
    size_t array_size = list_to_array(&array, list);
    if (array == NULL) {
        list_delete(list);
        return false;
    }
    printf("\nArray:");
    for (int i = 0; i < array_size; ++i)
        printf("%d ", array[i]);
    putchar('\n');
    free(array);

    list_delete(list);
    return true;
}

/** ---------- **/

/** MAIN **/
int main(void)
{

    assert(list_testcase1());
    assert(list_testcase2());
    assert(list_testcase3());
    assert(list_testcase4());
    assert(list_testcase5());
    assert(list_testcase6());
    assert(list_testcase7());
    assert(list_testcase8());
    assert(list_testcase9());
    assert(list_testcase10());

    return 0;
}
