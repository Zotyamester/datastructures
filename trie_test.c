#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "trie.h"


void f1()
{
    Trie *trie = trie_create();
    char buf[64];
    FILE *fp = fopen("words.txt", "r");
    while (fscanf(fp, "%s", buf) == 1) {
        trie_insert(trie, buf);
    }
    fclose(fp);
    puts("---SEARCH---");
    gets(buf);
    while (strcmp(buf, "q") != 0) {
        clock_t begin = clock();
        printf("%s is %s\n", buf, (trie_search(trie, buf) == true) ? "valid":"invalid");
        clock_t end = clock();
        printf("Result in %f seconds.\n", (double)(end - begin) / CLOCKS_PER_SEC);
        gets(buf);
    }
    trie_delete(trie);
}

void f2()
{
    char words[1000][64];
    char buf[64];
    int n = 0;
    FILE *fp = fopen("words.txt", "r");
    while (fscanf(fp, "%s", buf) == 1) {
        strcpy(words[n++], buf);
    }
    fclose(fp);
    puts("---SEARCH---");
    gets(buf);
    while (strcmp(buf, "q") != 0) {
        clock_t begin = clock();
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (strcmp(buf, words[i]) == 0) {
                printf("%s is valid\n", buf);
                found = true;
                break;
            }
        }
        if (!found) {
            printf("%s is invalid\n", buf);
        }
        clock_t end = clock();
        printf("Result in %f seconds.\n", (double)(end - begin) / CLOCKS_PER_SEC);
        gets(buf);
    }
}

int main(void)
{

    f1();
    //f2();

    return 0;
}
