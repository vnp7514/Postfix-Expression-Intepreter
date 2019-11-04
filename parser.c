// 
// File: parser.c
// Implementations of parser.h
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

/// From parser.h
///
void rep(char *exp){
}

/// From parser.h
///
tree_node_t *parse(stack_t *stack){
    return NULL;
}

/// From parser.h
/// 
tree_node_t *make_parse_tree(char* expr){
    return NULL;
}

/// From parser.h
///
int eval_tree(tree_node_t *node){
    return 0;
}

/// From parser.h
///
void print_infix(tree_node_t* node){
    if (node != NULL){
        if (node->type == LEAF){
            printf("%s", node->token);
        } else {
            tree_node_t* next = node->node;
            printf("(");
	    print_infix(next->left);
	    printf("%s", node->token);
	    print_infix(next->right);
            printf(")");
        }
    } else {
        fprintf(stderr, "Node is NULL when print_infix is called\n");
        exit(EXIT_FAILURE);
    }
}

/// Free the interior node from the dnamic memory
/// @param node the interior memory
///
void free_interior(interior_node_t* node){
    if (node != NULL){
        cleanup_tree(node->left);
        cleanup_tree(node->right);
        free(node);
    }
}

/// From parser.h
///
void cleanup_tree(tree_node_t* node){
    if (tree != NULL){
        free(tree->token);
        if (tree->type == INTERIOR){
            free_interior(tree->node);
        } else {
            free(tree->node); 
        }
        free(tree);
    }
}

// end
