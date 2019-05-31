#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"

/** Test cases **/

#define CREATE_LIST_TEMPLATE()                  \
            do {                                \
                list = create_list();           \
                if (list == NULL)               \
                    return false;               \
                for (int i = 1; i <= 5; ++i)    \
                    push_listback(list, i);     \
            } while(0)

/** Creating and printing **/
bool testcase1()
{
    printf("---TEST 1.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    /** Same as --> print_list(list, stdout); **/
    for (ListNode *iter = get_listbegin(list); iter != get_listend(); iter = get_listnext(iter)) {
        printf("%d ", iter->data);
    }
    putchar('\n');
    print_list(list, stdout);

    delete_list(list);
    return true;
}

/** Copying and reversing **/
bool testcase2()
{
    printf("---TEST 2.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    List *copy = copy_list(list);
    if (copy == NULL)
        return false;

    reverse_list(copy);

    printf("List:");
    print_list(list, stdout);
    printf("\nCopied list:");
    print_list(copy, stdout);
    putchar('\n');

    delete_list(list);
    delete_list(copy);
    return true;
}

/** Retrieving elements **/
bool testcase3()
{
    printf("---TEST 3.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    printf("%d\n", get_listindex(list, 0));
    printf("%d\n", get_listindex(list, 3));
    printf("%d\n", get_listindex(list, 1));
    printf("%d\n", get_listindex(list, 4));

    delete_list(list);
    return true;
}

/** Popping from back and front **/
bool testcase4()
{
    printf("---TEST 4.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    printf("%d\n", pop_listhead(list));
    printf("%d\n", pop_listhead(list));
    printf("%d\n", pop_listback(list));
    printf("%d\n", pop_listback(list));

    delete_list(list);
    return true;
}

bool testcase5()
{
    printf("---TEST 5.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    remove_listitem(list, 1);
    remove_listitem(list, 3);
    remove_listitem(list, 5);
    print_list(list, stdout);
    putchar('\n');

    delete_list(list);
    return true;
}

/** Creating from array **/
bool testcase6()
{
    printf("---TEST 6.---\n");
    int array[5] = {1, 2, 3, 4, 5};
    List *list = create_list_from_array(array, 5);
    if (list == NULL)
        return false;

    printf("Array:");
    for (int i = 0; i < 5; ++i)
        printf("%d ", array[i]);

    printf("\nList:");
    print_list(list, stdout);
    putchar('\n');

    delete_list(list);
    return true;
}

/** Scanning from input **/
bool testcase7()
{
    printf("---TEST 7.---\nEnter the values:");
    List *list = scan_list(stdin);
    if (list == NULL)
        return false;

    print_list(list, stdout);
    putchar('\n');
    return true;
}

/** Iterators **/
bool testcase8()
{
    printf("---TEST 8.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    for (ListNode *iter = get_listbegin(list); iter != get_listend(); iter = get_listnext(iter)) {
        printf("iter->data = %d\n", iter->data);
    }

    delete_list(list);
    return true;
}

/** Link lists together **/
bool testcase9()
{
    printf("---TEST 9.---\n");
    List *list = create_list(), *list2 = create_list();
    if (list == NULL) {
        if (list2 != NULL)
            delete_list(list2);
        return false;
    } else if (list2 == NULL) {
        delete_list(list);
        return false;
    }
    for (int i = 1; i <= 5; ++i)
        push_listback(list, i);
    for (int i = 6; i <= 10; ++i)
        push_listback(list2, i);

    link_list(list, list2);

    print_list(list, stdout);
    putchar('\n');

    delete_list(list);
    delete_list(list2);
    return true;
}

/** General test **/
bool testcase10()
{
    printf("---TEST 10.---\n");

    List *list;
    CREATE_LIST_TEMPLATE();

    ListNode *a = get_listbegin(list);
    ListNode *b = get_listnext(a);
    int cmp = cmp_listnodes(a, b);
    printf("Comparison --> %d %c %d\n", a->data, ((cmp == -1) ? '<' : ((cmp == 0) ? '=' : '>')), b->data);
    remove_listnode(list, a);

    printf("List:");
    print_list(list, stdout);
    int *array = NULL;
    size_t array_size = list_to_array(&array, list);
    if (array == NULL) {
        delete_list(list);
        return false;
    }
    printf("\nArray:");
    for (int i = 0; i < array_size; ++i)
        printf("%d ", array[i]);
    putchar('\n');
    free(array);

    delete_list(list);
    return true;
}

/** ---------- **/

/** MAIN **/
int main(void)
{

    assert(testcase1());
    assert(testcase2());
    assert(testcase3());
    assert(testcase4());
    assert(testcase5());
    assert(testcase6());
    assert(testcase7());
    assert(testcase8());
    assert(testcase9());
    assert(testcase10());

    return 0;
}
