#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void RBT_left_rotation(RBTRoot *root,RBTNode * X)
{
    RBTNode *Y = X->right;

    X->right = Y->left;
    if(Y->left != NULL)
        Y->left->parent = X;

    Y->parent = X->parent;
    if(X->parent == NULL)
        root->node = Y;
    else if(X->parent->left == X)
        X->parent->left = Y;
    else
        X->parent->right = Y;

    Y->left = X;
    X->parent = Y;
}

void RBT_right_rotation(RBTRoot *root,RBTNode * Y)
{
    RBTNode *X = Y->left;

    Y->left = X->right;
    if(X->right != NULL)
        X->right->parent = Y;

    X->parent = Y->parent;
    if(Y->parent == NULL)
        root->node = X;
    else if(Y->parent->left == Y)
        Y->parent->left = X;
    else
        Y->parent->right = X;

    X->right = Y;
    Y->parent = X;
}

int RBT_insert_key(RBTRoot *root,int key)
{
    RBTNode *node;
    if((node = RBT_create_node(key,NULL,NULL,NULL)) == NULL )
        return -1;

    RBT_insert(root,node);

    return 0;
}

RBTRoot* RBT_create()
{
    RBTRoot *root = (RBTRoot*)malloc(sizeof(RBTRoot));
    if(root == NULL) {
        fprintf(stderr,"allocating memory error \n");
        exit(EXIT_FAILURE);
    }

    root->node = NULL;
    return root;
}

RBTNode* RBT_create_node(int key,RBTNode *parent,RBTNode *left,RBTNode *right)
{
    RBTNode *node = (RBTNode *)malloc(sizeof(RBTNode));
    if(node == NULL) {
        fprintf(stderr,"allocating memory fails\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = left;
    node->right = right;
    node->parent = parent;
    node->color = BLACK;

    return node;
}

void RBT_insert(RBTRoot *root,RBTNode *node)
{
    RBTNode *Y = NULL;
    RBTNode *X = root->node;

    while(X != NULL) {
        Y = X;
        if(node->key < X->key)
            X = X->left;
        else
            X = X->right;
    }

    node->parent = Y;

    if(Y != NULL)
        if(node->key < Y->key)
            Y->left = node;
        else
            Y->right = node;
    else
        root->node = node;

    node->color = RED;
    RBT_insert_fixup(root,node);

}

void RBT_insert_fixup(RBTRoot *root,RBTNode *node)
{
    RBTNode *parent,*gparent;
    while((parent = node->parent) && parent->color == RED) {
        gparent = parent->parent;

        if(parent == gparent->left) {

            RBTNode *uncle = gparent->right;

            if(uncle && uncle->color == RED) {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
                continue;
            }

            if(parent->right == node) {
                RBTNode *tmp;
                RBT_left_rotation(root,parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->color = BLACK;
            gparent->color = RED;
            RBT_right_rotation(root,gparent);

        } else {

            RBTNode *uncle = gparent->left;

            if(uncle && uncle->color == RED) {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
                continue;
            }

            if(parent->left == node) {
                RBTNode *tmp;
                RBT_right_rotation(root,parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->color = BLACK;
            gparent->color = RED;
            RBT_left_rotation(root,gparent);

        }

    }

    root->node->color = BLACK;

}

void RBT_destroy(RBTNode *node)
{
    if(node != NULL) {
        RBT_destroy(node->left);
        RBT_destroy(node->right);
        free(node);
        node = NULL;
    }
}


