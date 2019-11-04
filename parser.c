// 
// File: parser.c
// Implementations of parser.h
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <stdbool.h>
#include <string.h>

/// From parser.h
///
void rep(char *exp){
}

/// Check whether the token is an operation
/// @param token the token to be checked
/// @return true if token is an operation, false otherwise
///
bool is_op(char *token){
    return strcmp(token, ADD_OP_STR) == 0 ||
        strcmp(token, SUB_OP_STR) == 0 ||
        strcmp(token, MUL_OP_STR) == 0 ||
        strcmp(token, DIV_OP_STR) == 0 ||
        strcmp(token, MOD_OP_STR) == 0 ||
        strcmp(token, Q_OP_STR) == 0 ||
        strcmp(token, ASSIGN_OP_STR) == 0;
}

/// Convert the token into the enum op_type_e
/// @param token the token
/// @return a value within the op_type_t enum
///
op_type_t toOP(char* token){
    if (strcmp(token, ADD_OP_STR) == 0){
        return ADD_OP;
    } else if (strcmp(token, SUB_OP_STR) == 0){
        return SUB_OP;
    } else if (strcmp(token, MUL_OP_STR) == 0){
        return MUL_OP;
    } else if (strcmp(token, DIV_OP_STR) == 0){
        return DIV_OP;
    } else if (strcmp(token, MOD_OP_STR) == 0){
        return MOD_OP;
    } else if (strcmp(token, ASSIGN_OP_STR) == 0){
        return ASSIGN_OP;
    } else if (strcmp(token, Q_OP_STR) == 0){
        return Q_OP;
    } else {
        fprintf(stderr, "Invalid operation string!\n");
	exit(EXIT_FAILURE); 
    }
}

/// From parser.h
///
tree_node_t *parse(stack_t *stack){
    tree_node_t* node = NULL;
    char *token = top(stack);
    pop(stack);
    if (is_op(token)){
        op_type_t op = toOP(token);
	tree_node_t* left = parse(stack);
	tree_node_t* right = parse(stack);
	node = make_interior(op, token, left, right);
    } else {
        char *endptr;
        strtol(token, &endptr, 10);
        if (endptr == token){// Should be a symbol
           node = make_leaf(SYMBOL, token);
        } else if (*endptr != 0){//there are characters after number
           fprintf(stderr, "BAD NUMBER in parse() in parser.c\n");
           exit(EXIT_FAILURE);
        } else {
	   node = make_leaf(INTEGER, token); 
	}
    }
    return node;
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
            interior_node_t* next = (interior_node_t*) node->node;
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
    if (node != NULL){
        free(node->token);
        if (node->type == INTERIOR){
            free_interior(node->node);
        } else {
            free(node->node); 
        }
        free(node);
    }
}

// end
