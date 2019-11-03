// 
// File: tree_node.c
// Implementation of tree_node.h
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include "tree_node.h"
#include <string.h>

/// From tree_node.h
///
tree_node_t *make_interior(op_type_t op, char *token, 
               tree_node_t *left, tree_node_t *right){
    tree_node_t* tree = (tree_node_t *) calloc(1, sizeof(tree_node_t));
    tree->type = INTERIOR;
    tree->token = (char *) calloc(1, strlen(token)+1);
    strcpy(tree->token, token);
    interior_node_t* node = 
        (interior_node_t *) calloc(1, sizeof(interior_node_t));
    node->op = op;
    node->left = left;
    node->right = right;
    tree->node = node;
    return tree;
}

/// From tree_node.h
///
tree_node_t *make_leaf(exp_type_t exp_type, char *token){
    tree_node_t *tree = (tree_node_t *) calloc(1, sizeof(tree_node_t));
    tree->type = LEAF;
    tree->token = (char*) calloc (1, strlen(token)+1);
    strcpy(tree->token, token);
    leaf_node_t* node = (leaf_node_t *) calloc(1, sizeof(leaf_node_t));
    node->exp_type = exp_type;
    tree->node = node;
    return tree;
}

void free_interior(interior_node_t *node);

/// Free the tree from the dynamic memory
/// @param tree the tree node
///
void free_tree(tree_node_t *tree){
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

/// Free the interior node from the dynamic memory
/// @param node the interior node
///
void free_interior(interior_node_t *node){
     if (node != NULL){
         free_tree(node->left);
         free_tree(node->right);
         free(node);
     }
}

#if 0
############################################################
#Testing functions for tree_node to check for memory errors#
############################################################
/// Testing make_leaf() function
///
void test_make_leaf(){
    char *x = "x";
    tree_node_t *tree = make_leaf(SYMBOL, x);
    free_tree(tree);
}

/// Testing make_interior() function
///
void test_make_interior(){
    char *x = "x";
    tree_node_t *tree = make_interior(ADD_OP, x, NULL, NULL);
    free_tree(tree);
}

/// Testing all functions
///
void test(){
    test_make_leaf();
    test_make_interior();
}

/// Test whether the functions work
/// @returns errorCode  error Code; EXIT_SUCCESS if no error
///
int main() {
    test();
    return EXIT_SUCCESS ;
}
#endif

#// end
