// 
// File: symtab.c
// Make a symbol table
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

static symbol_t *table = NULL;

/// Freeing the memory allocations used by the symbol
/// @param symbol  a pointer to the symbol
///
void free_symbol_t(symbol_t *symbol){
    if (symbol != NULL){
        free(symbol->var_name);
        free_symbol_t(symbol->next);
        free(symbol);
    }
}

/// From symtab.h
///
void free_table(){
    free_symbol_t(table); 
}

/// from symtab.h
///
void build_table(char *filename){
    if (filename != NULL){
	    
        FILE *file = fopen(filename, "r");
	if (file == NULL){
            fprintf(stderr, "Failed to open file!");
            exit(EXIT_FAILURE);

        } else {

	    char name[BUFLEN];
	    char value[BUFLEN];
	    int result;
	    symbol_t* current = NULL;
	    
            while ((result = fscanf(file, "%s %s \n", name, value)) == 2){
                //Making a new node
                symbol_t* new = (symbol_t*) calloc(1, sizeof(symbol_t));
	        new->var_name = (char *) calloc(BUFLEN, sizeof(char));
                strncpy(new->var_name, name, BUFLEN);

		char *ptr;
                new->val = strtol(value, &ptr, 10);
		if (ptr == value){//not an int
                    free(new->var_name);
		    free(new);
                    free_table();
		    fprintf(stderr, 
                       "Symbol Table text is not formatted correctly\n");
		    exit(EXIT_FAILURE);
		}
                if (table == NULL){//first node
		    table = new;
		} else {
		    current->next = new;
		}
		current = new;
	    
	    }
        
	}

	fclose( file );
    }
}

/// From symtab.h
///
void dump_table(){
    symbol_t *current = table;
    if (current != NULL){
        printf("SYMBOL TABLE:\n");
        while (current != NULL){
            printf("\tName: %s, Value: %d\n", current->var_name, current->val);
            current = current->next;
        }
    }
}

/// From symtab.h
///
symbol_t *lookup_table(char *variable){
    symbol_t *target = NULL;
    symbol_t *current = table;
    while (current != NULL){
        if (strcmp(current->var_name, variable) == 0){
	    target = current;
	    break;
	} else {
	    current = current->next;
	}
    }
    return target;
}

/// From symtab.h
///
symbol_t *create_symbol(char *name, int val){
    symbol_t *new = (symbol_t *) calloc(1, sizeof(symbol_t));
    new->var_name = (char *) calloc (BUFLEN, sizeof(char));
    strncpy(name, new->var_name, BUFLEN);
    new->val = val;
    symbol_t *current = table;
    symbol_t *prev = NULL;
    while (current != NULL){
        prev = current;
        current = current->next;
    }
    prev->next = new;
    return new;
}


// end
