#include <stdio.h>
#include "queue.h"

int main(void)
{
    Queue *queue = queue_create();
    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);
    queue_push(queue, 5);
    queue_pop(queue);
    queue_print(queue, stdout);
    queue_delete(queue);
    return 0;
}
