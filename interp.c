// 
// File: interp.c
// This is the implementation of the interp.h. _TO_DO
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interp.h"
#include "symtab.h"
#include "parser.h"


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
    printf("Enter postfix expressions (CTRL-D to exit):\n> ");
    char line[MAX_LINE+1];
    while (fgets(line, MAX_LINE+1, stdin) != NULL){
        if (line[strlen(line) - 1] != '\n'){
            fprintf(stderr, "Input line too long\n");
            while(line[strlen(line) - 1] != '\n'){
                fgets(line, MAX_LINE+1, stdin);
            }
        } else {
            char* exp = (char*) calloc(MAX_LINE, sizeof(char));
	    strncpy(exp, line, strlen(line)); //excluding the '\n' character
            char* cmt = strchr(exp, '#');
            char* endl = strchr(exp, '\n');
            char* eof = strchr(exp, EOF);
            if (cmt != NULL){
                *cmt = '\0';
            }
            if (endl != NULL){
                *endl = '\0';
            }
            if (eof != NULL){
                *eof = '\0';
            }
            if ((int) strlen(exp) != 0){
                rep(exp);
            }
            free(exp);
        }
        printf("> ");
    }
    printf("\n");
    dump_table();
    free_table();
    
    return EXIT_SUCCESS ;
}

// end
