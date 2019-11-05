// 
// File: tree_node.c
// Implementation of tree_node.h
// @author Nguyen Dinh Van Pham <vnp7514@rit.edu>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_node.h"


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

// end
