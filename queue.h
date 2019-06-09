#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef List Queue;

inline Queue *queue_create()
{
    return list_create();
}
inline void queue_push(Queue *queue, int data)
{
    list_push_front(queue, data);
}
inline void queue_pop(Queue *queue)
{
    list_pop_back(queue);
}
inline int queue_top(Queue *queue)
{
    return list_get_back(queue);
}
inline void queue_print(Queue *queue, FILE *fp)
{
    list_print(queue, fp);
}
inline void queue_clear(Queue *queue)
{
    list_clear(queue);
}
inline void queue_delete(Queue *queue)
{
    list_delete(queue);
}

#endif /* QUEUE_H */
