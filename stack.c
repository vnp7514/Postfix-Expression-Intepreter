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

/// Assuming nodes have data as integer pointers
///
void print_node(stack_node_t *node){
    if (node != NULL){
        printf("%d ", *((int *)(node->data)));
        print_node(node->next);	
    } else{
        printf("\n");
    }
}

///Printing out the stack
///
void print_stack(stack_t *stack){
    if (stack == NULL){
        return;
    } 
    print_node(stack->top);
}

///Testing make_stack()
///
void test_make_stack(){
    printf("Testing make_stack()\n");
    stack_t *stack = make_stack();
    printf("Printing empty stack: ");
    print_stack(stack);
    printf(empty_stack(stack) ? "Stack is empty\n" : "Stack is not empty\n");
    printf("\n");
    free_stack(stack);
}

///Testing top()
/// @param mode 0 for testing top on an empty stack---should exit
///  Otherwise, testing top on a nonempty stack
///
void test_top(int mode){
    printf("Testing top()\n");
    stack_t *stack = make_stack();
    if (mode == 0){
        printf(empty_stack(stack) ? "Stack is empty\n"
                     : "Stack is not empty\n");
        printf("Top of the stack: %d", *((int *)top(stack)));
    } else {
        printf("Pushing %d onto the stack\n", mode);
        push(stack, &mode);
        printf(empty_stack(stack) ? "Stack is empty\n" :
                      "Stack is not empty\n");
        printf("Top of the stack: %d\n", *((int *)top(stack)));
    }
    free_stack(stack);
}

///Testing push() 
///
void test_push(){
    printf("Testing push()\n");
    stack_t *stack = make_stack();
   
    printf("Adding 25 to the stack\n");
    int a = 25;
    push(stack, &a);
    printf("Adding 35 to the stack\n");
    int b = 35;
    push(stack, &b);
    printf(empty_stack(stack) ? "Stack is empty\n" : "Stack is not empty\n");
    print_stack(stack);
    free_stack(stack);
 
}

///Testing pop()
/// @oaram mode 0 if you do not want to test the error reporting
///             otherwise, it will produce an error. 
///
void test_pop(int mode){
    printf("Testing pop()\n");
    stack_t *stack = make_stack();
    if (mode == 0){
        printf("Adding 25 to the stack\n");
        int a = 25;
        push(stack, &a);
        printf("Adding 35 to the stack\n");
        int b = 35;
        push(stack, &b);
        printf(empty_stack(stack) ? "Stack is empty\n" : 
                                    "Stack is not empty\n");
        print_stack(stack);
        printf("Popping...\n");
        pop(stack);
        printf(empty_stack(stack) ? "Stack is empty\n" : 
                                    "Stack is not empty\n");
        print_stack(stack);
        printf("Popping...\n");
        pop(stack);
        printf(empty_stack(stack) ? "Stack is empty\n" : 
                                    "Stack is not empty\n");
        print_stack(stack);
    } else {
        pop(stack);
    }
    free_stack(stack);
}

/// Testing stack functions
///
void test(){
    test_make_stack();
    printf("\n");
    //test_top(0);//Commented out if do not want to check for error reporting
    test_top(5);
    printf("\n");
    test_push();
    printf("\n");
    //test_pop(1);//Commented out if do not want to check for error reporting
    test_pop(0);    
}

/// Doing some testings
/// @returns errorCode  error Code; EXIT_SUCCESS if no error
///
int main() {
    test();
    return EXIT_SUCCESS ;
}

// end
