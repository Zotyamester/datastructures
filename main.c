#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/* Libs */
#include "list.h"
#include "tree.h"
#include "hashtable.h"

/* Test cases */

bool testcase1()
{
    List *list = create_list();
    if (list == NULL)
        return 1;
    add_listback(list, 1);
    add_listback(list, 2);
    add_listback(list, 3);
    add_listback(list, 4);
    add_listback(list, 5);

    /** Same as --> print_list(list, stdout); **/
    for (ListNode *iter = get_listbegin(list); iter != get_listend(); iter = get_listnext(iter)) {
        printf("%d ", iter->data);
    }
    putchar('\n');
    print_list(list, stdout);

    delete_list(list);
}

bool testcase2()
{
}

bool testcase3()
{
}

bool testcase4()
{
}

bool testcase5()
{
}

bool testcase6()
{
}

bool testcase7()
{
}

bool testcase8()
{
}

bool testcase9()
{
}


bool testcase10()
{
}

/* ---------- */

int main(void)
{

    assert(testcase1());

    return 0;
}
