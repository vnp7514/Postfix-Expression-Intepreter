// 
// File: stack.c 
// Implementation of a stack following stack.h
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/// From stack.h
///
stack_t *make_stack(void){
    stack_t* stack = (stack_t*) calloc(1, sizeof(stack_t));
    stack->top = NULL;
    return stack;
}

/// From stack.h
/// 
void push(stack_t *stack, void *data){
    stack_node_t* node = (stack_node_t*) calloc(1, sizeof(stack_node_t));
    node->data = data;
    node->next = NULL;
    if (stack->top != NULL){
        node->next = stack->top;
    }
    stack->top = node;
}

/// From stack.h
///
void *top(stack_t *stack){
    if (stack->top == NULL){
        fprintf(stderr, "Stack was empty when top was called\n");
        exit(EXIT_FAILURE);
    }
    return (stack->top)->data;
}

/// From stack.h
///
void pop(stack_t *stack){
    if (stack->top == NULL){
        fprintf(stderr, "Stack was empty when pop was called\n");
        exit(EXIT_FAILURE);
    }
    stack_node_t* node = stack->top;
    stack->top = node->next;
    free(node);
}

/// From stack.h
///
int empty_stack(stack_t *stack){
    if (stack->top == NULL){
        return 1;//True
    } else {
        return 0;//False
    }
}

/// From stack.h
///
void free_stack(stack_t *stack){
    if (stack->top == NULL){
        free(stack);  
    } else {
        stack_node_t* node = stack->top;
	stack->top = node->next;
	free (node);
	free_stack(stack);
    }
}

// end
