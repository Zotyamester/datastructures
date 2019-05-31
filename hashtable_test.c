#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hashtable.h"

/** Test cases **/

bool hashtable_testcase1()
{
    printf("---TEST 1.---\n");
    HashTable *ht = create_hashtable();
    delete_hashtable(ht);
    return true;
}

bool hashtable_testcase2()
{

}

bool hashtable_testcase3()
{

}

bool hashtable_testcase4()
{

}

bool hashtable_testcase5()
{

}

bool hashtable_testcase6()
{

}

bool hashtable_testcase7()
{

}

bool hashtable_testcase8()
{

}

bool hashtable_testcase9()
{

}

bool hashtable_testcase10()
{

}

/** ---------- **/

/** MAIN **/
int main(void)
{

    assert(hashtable_testcase1());
    /*assert(hashtable_testcase2());
    assert(hashtable_testcase3());
    assert(hashtable_testcase4());
    assert(hashtable_testcase5());
    assert(hashtable_testcase6());
    assert(hashtable_testcase7());
    assert(hashtable_testcase8());
    assert(hashtable_testcase9());
    assert(hashtable_testcase10());*/

    return 0;
}
