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

static parse_error_t error = PARSE_NONE;

void print_error(){
    switch (error){
        case TOO_FEW_TOKENS:
            fprintf(stderr, "Invalid expression, not enough tokens\n");
            break;
         case TOO_MANY_TOKENS:
            fprintf(stderr, "Invalid expression, too many tokens\n");
            break;
         case INVALID_ASSIGNMENT:
            fprintf(stderr, "Invalid assignment\n");
            break;
         case ILLEGAL_TOKEN:
            fprintf(stderr, "Illegal token\n");
            break;
         default:
            break;
    }
    error = PARSE_NONE;
}

/// From parser.h
///
void rep(char *exp){
    tree_node_t *tree = make_parse_tree(exp);
    if (error == PARSE_NONE){
        int result = eval_tree(tree);
	print_infix(tree);
	printf(" = %d\n", result);
    } else {
        print_error();
    }
    cleanup_tree(tree);
}

/// Check whether the token is an operation
/// @param token the token to be checked
/// @return true if token is an operation, false otherwise
///
bool is_op(const char *token){
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
op_type_t toOP(const char* token){
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
        fprintf(stderr, "Something is wrong with is_op()\n");
	exit(EXIT_FAILURE); 
    }
}

/// Check whether the token is an alphanumeric string
/// @param token the token
/// @return true if token is alphanumeric. false otherwise
///
bool is_alphanumeric(const char *token){
    for (unsigned int i = 0; i < strlen(token); i++){
        if (!((token[i] >= 48 && token[i] <= 57) ||//digit
            (token[i] >= 65 && token[i] <= 90) ||//uppercase
            (token[i] >= 97 && token[i] <= 122))){//lowercase
            return false;
	}
    }
    return true;
}

/// Check whether the node is a symbol node
/// @param node the pointer to a tree_node_t structure
///return true if it is a symbol, false otherwise
///
bool is_symbol(tree_node_t* node){
    if (node != NULL){
        if (node->type == LEAF){
            if ( ( (leaf_node_t*) (node->node) ) ->exp_type == SYMBOL ){
                return true;  
            }
        }
    }
    return false;
}

/// From parser.h
///
tree_node_t *parse(stack_t *stack){
    tree_node_t* node = NULL;
    if (error == PARSE_NONE){
        if (!empty_stack(stack)){
            char *token = top(stack);
            pop(stack);
            if (is_op(token)){
                op_type_t op = toOP(token);
                tree_node_t* right = parse(stack);
                tree_node_t* left = parse(stack);
                if (op == ASSIGN_OP && !is_symbol(left)){
                    error = INVALID_ASSIGNMENT;
                }
	        node = make_interior(op, token, left, right);
            } else {
                char *endptr;
                strtol(token, &endptr, 10);
                if (endptr == token){// Should be a symbol
                    if (!is_alphanumeric(token)){
		        error = ILLEGAL_TOKEN;
		    } else {
                        node = make_leaf(SYMBOL, token);
                    }
                    } else if (*endptr != 0){
                    //there are characters after number
                        error = ILLEGAL_TOKEN;
                    } else {
                        node = make_leaf(INTEGER, token); 
	            }
            }
        } else {
            error = TOO_FEW_TOKENS;
        }
    }
    return node;
}

/// From parser.h
/// 
tree_node_t *make_parse_tree(char* expr){
    char *token;
    stack_t* stack = make_stack();
    token = strtok(expr, " ");
    while ((token) != NULL){
        push(stack, (void *) token);
        token = strtok(NULL, " ");
    } 
    tree_node_t* tree = parse(stack);
    if (!empty_stack(stack) && error == PARSE_NONE){
        error = TOO_MANY_TOKENS;
    }
        
    free_stack(stack);
    return tree;

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
            if (node->node != NULL){	
                free(node->node); 
            }
        }
        free(node);
    }
}

// end
