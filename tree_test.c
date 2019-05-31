#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "tree.h"

/** Test cases **/

bool tree_testcase1()
{
    Tree *tree = create_tree();

    delete_tree(tree);
    return true;
}

bool tree_testcase2()
{

}

bool tree_testcase3()
{

}

bool tree_testcase4()
{

}

bool tree_testcase5()
{

}

bool tree_testcase6()
{

}

bool tree_testcase7()
{

}

bool tree_testcase8()
{

}

bool tree_testcase9()
{

}

bool tree_testcase10()
{

}

/** ---------- **/

/** MAIN **/
int main(void)
{

    assert(tree_testcase1());
    /*assert(tree_testcase2());
    assert(tree_testcase3());
    assert(tree_testcase4());
    assert(tree_testcase5());
    assert(tree_testcase6());
    assert(tree_testcase7());
    assert(tree_testcase8());
    assert(tree_testcase9());
    assert(tree_testcase10());*/

    return 0;
}
