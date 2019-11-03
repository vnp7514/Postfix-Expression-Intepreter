// 
// File: interp.c
// This is the implementation of the interp.h. _TO_DO
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include "interp.h"
#include "symtab.h"

/// The program should runs with one optional argument. If there are
///   more arguments, an error will be returned.
/// @param argc  number of command line arguments, including program name
/// @param argv  supplied command line arguments, including program name
/// @returns errorCode  error Code; EXIT_SUCCESS if no error

int main( int argc, char* argv[] ) {

    char *file_name = NULL;
    if (argc > 2) {
        fprintf(stderr, "Usage: interp [sym-table]\n");
	exit(EXIT_FAILURE);
    } else if (argc == 2){
        file_name = argv[1];
    }
    build_table(file_name);
    dump_table();
    printf("Enter postfix expressions (CTRL-D to exit):\n");
    int result;
    while ((result = getchar()) != EOF){
        printf("%c", result);
    }

    
    return EXIT_SUCCESS ;
}

// end
