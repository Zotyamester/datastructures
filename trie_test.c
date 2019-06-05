#include <stdio.h>
#include <stdbool.h>
#include "trie.h"

int main(void)
{

    Trie *trie = trie_create();
    char buf[32];
    puts("---INPUT---");
    for (int i = 0; i < 3; ++i) {
        gets(buf);
        trie_insert(trie, buf);
    }
    puts("---SEARCH---");
    for (int i = 0; i < 3; ++i) {
        gets(buf);
        printf("%s is %s\n", buf, (trie_search(trie, buf) == true) ? "valid":"invalid");
    }
    puts("---PRINT---");
    trie_print(trie);
    trie_delete(trie);

    return 0;
}
