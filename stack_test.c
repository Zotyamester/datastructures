#include <stdio.h>
#include "stack.h"

int main(void)
{
    Stack *stack = stack_create();
    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);
    stack_push(stack, 4);
    stack_push(stack, 5);
    stack_pop(stack);
    stack_print(stack, stdout);
    stack_delete(stack);
    return 0;
}
