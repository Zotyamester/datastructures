#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/* Libs */
#include "list.h"
#include "tree.h"
#include "hashtable.h"

/** Test cases **/

/** Creating and printing **/
bool testcase1()
{
    printf("---TEST 1.---\n");
    List *list = create_list();
    if (list == NULL)
        return false;
    for (int i = 1; i <= 5; ++i)
        push_listback(list, i);

    /** Same as --> print_list(list, stdout); **/
    for (ListNode *iter = get_listbegin(list); iter != get_listend(); iter = get_listnext(iter)) {
        printf("%d ", iter->data);
    }
    putchar('\n');
    print_list(list, stdout);

    delete_list(list);
    return true;
}

/** Copying **/
bool testcase2()
{
    printf("---TEST 2.---\n");
    List *list = create_list();
    if (list == NULL)
        return false;
    for (int i = 1; i <= 5; ++i)
        push_listback(list, i);

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
    List *list = create_list();
    if (list == NULL)
        return false;
    for (int i = 1; i <= 5; ++i)
        push_listback(list, i);

    printf("%d\n", get_listindex(list, 0));
    printf("%d\n", get_listindex(list, 3));
    printf("%d\n", get_listindex(list, 1));
    printf("%d\n", get_listindex(list, 4));
    return true;
}

/** Popping from back and front **/
bool testcase4()
{
    printf("---TEST 4.---\n");
    List *list = create_list();
    if (list == NULL)
        return false;
    for (int i = 1; i <= 5; ++i)
        push_listback(list, i);

    printf("%d\n", pop_listhead(list));
    printf("%d\n", pop_listhead(list));
    printf("%d\n", pop_listback(list));
    printf("%d\n", pop_listback(list));
    return true;
}

bool testcase5()
{
    printf("---TEST 5.---\n");
    List *list = create_list();
    if (list == NULL)
        return false;
    for (int i = 1; i <= 5; ++i)
        push_listback(list, i);

    remove_listitem(list, 1);
    remove_listitem(list, 3);
    remove_listitem(list, 5);
    print_list(list, stdout);
    putchar('\n');
    return true;
}

bool testcase6()
{
    return true;
}

bool testcase7()
{
    return true;
}

bool testcase8()
{
    return true;
}

bool testcase9()
{
    return true;
}


bool testcase10()
{
    return true;
}

/* ---------- */

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
