#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef List Stack;

inline Stack *stack_create()
{
    return list_create();
}
inline void stack_push(Stack *stack, int data)
{
    list_push_back(stack, data);
}
inline void stack_pop(Stack *stack)
{
    list_pop_back(stack);
}
inline int stack_top(Stack *stack)
{
    return list_get_back(stack);
}
inline void stack_print(Stack *stack, FILE *fp)
{
    list_print(stack, fp);
}
inline void stack_clear(Stack *stack)
{
    list_clear(stack);
}
inline void stack_delete(Stack *stack)
{
    list_delete(stack);
}

#endif /* STACK_H */
