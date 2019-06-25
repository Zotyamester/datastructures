/**
 * \file queue.h
 *
 * This file contains adapter functions for queues.
 * The queue's implementation can be either a list or a vector depending on the macro.
 * (By default its implementations is a vector.)
 * @author Zoltan Szatmary
 *
 **/

#ifndef QUEUE_H
#define QUEUE_H

/** If the 'LIST_QUEUE' macro is defined, then it's going to be a list. **/
#ifdef LIST_QUEUE
#include "list.h"
typedef List Queue;
#else
#include "vector.h"
typedef Vector Queue;
#endif

inline Queue *queue_create()
{
#ifdef LIST_QUEUE
    return list_create();
#else
    return vector_create();
#endif
}
inline void queue_push(Queue *queue, int data)
{
#ifdef LIST_QUEUE
    list_push_front(queue, data);
#else
    vector_push_front(queue, data);
#endif
}
inline void queue_pop(Queue *queue)
{
#ifdef LIST_QUEUE
    list_pop_back(queue);
#else
    vector_pop_back(queue);
#endif
}
inline int queue_top(Queue *queue)
{
#ifdef LIST_QUEUE
    return list_back(queue);
#else
    return vector_back(queue);
#endif
}
inline size_t queue_size(Queue *queue)
{
#ifdef LIST_QUEUE
    return list_size(queue);
#else
    return vector_size(queue);
#endif
}
inline bool queue_empty(Queue *queue)
{
#ifdef LIST_QUEUE
    return list_empty(queue);
#else
    return vector_empty(queue);
#endif
}
inline void queue_print(Queue *queue, FILE *fp)
{
#ifdef LIST_QUEUE
    list_print(queue, fp);
#else
    vector_print(queue, fp);
#endif
}
inline void queue_clear(Queue *queue)
{
#ifdef LIST_QUEUE
    list_clear(queue);
#else
    vector_clear(queue);
#endif
}
inline void queue_delete(Queue *queue)
{
#ifdef LIST_QUEUE
    list_delete(queue);
#else
    vector_delete(queue);
#endif
}

#endif /* QUEUE_H */
