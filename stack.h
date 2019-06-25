/**
 * \file stack.h
 *
 * This file contains adapter functions for stacks.
 * The stack can be either a list or a vector depending on the macro.
 * (By default its implementations is a vector.)
 * @author Zoltan Szatmary
 *
 **/

#ifndef STACK_H
#define STACK_H

/** If the 'LIST_STACK' macro is defined, then it's going to be a list. **/
#ifdef LIST_STACK
#include "list.h"
typedef List Stack;
#else
#include "vector.h"
typedef Vector Stack;
#endif

inline Stack *stack_create()
{
#ifdef LIST_STACK
    return list_create();
#else
    return vector_create();
#endif
}
inline void stack_push(Stack *stack, int data)
{
#ifdef LIST_STACK
    list_push_back(stack, data);
#else
    vector_push_back(stack, data);
#endif
}
inline void stack_pop(Stack *stack)
{
#ifdef LIST_STACK
    list_pop_back(stack);
#else
    vector_pop_back(stack);
#endif
}
inline int stack_top(Stack *stack)
{
#ifdef LIST_STACK
    return list_back(stack);
#else
    return vector_back(stack);
#endif
}
inline size_t stack_size(Stack *stack)
{
#ifdef LIST_STACK
    return list_size(stack);
#else
    return vector_size(stack);
#endif
}
inline bool stack_empty(Stack *stack)
{
#ifdef LIST_STACK
    return list_empty(stack);
#else
    return vector_empty(stack);
#endif
}
inline void stack_print(Stack *stack, FILE *fp)
{
#ifdef LIST_STACK
    list_print(stack, fp);
#else
    vector_print(stack, fp);
#endif
}
inline void stack_clear(Stack *stack)
{
#ifdef LIST_STACK
    list_clear(stack);
#else
    vector_clear(stack);
#endif
}
inline void stack_delete(Stack *stack)
{
#ifdef LIST_STACK
    list_delete(stack);
#else
    vector_delete(stack);
#endif
}

#endif /* STACK_H */
