// 
// File: stack.c 
// TODO_DOCS_ touch.c
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/// From stack.h
///
stack_t *make_stack(void){
    stack_t stack = calloc(1, sizeof(stack_t));
    stack->top = NULL;
    return stack;
}

/// From stack.h
/// 
void push(stack_t *stack, void *data){
}

/// TODO_ provide function purpose documentation -- its 'docstring'
/// TODO_ if main takes no args, change to "main( void )" and remove //@params
/// @param argc  number of command line arguments, including program name
/// @param argv  supplied command line arguments, including program name
/// @returns errorCode  error Code; EXIT_SUCCESS if no error

int main( int argc, char* argv[] ) {

    // TODO_ indentation should be at least 3 spaces; 2 is not enough.

    // TODO_ wrap code lines when they get 'long' (~80 chars). 
    printf( "TODO_ %s received %i command line arguments.\n",
            argv[0], argc );

#if 0
    // TODO_ how to exclude code from compilation instead of commenting out.
#endif

    return EXIT_SUCCESS ;
}

// end
