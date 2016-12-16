#ifndef RBTREE_H
#define RBTREE_H

typedef unsigned char byte;

typedef struct __RED_BLACK_TREE_Root RBTRoot;
typedef struct __RED_BLACK_TREE_Node RBTNode;

#define RED 0
#define BLACK 1

struct __RED_BLACK_TREE_Root {
    RBTNode *node;
};

struct __RED_BLACK_TREE_Node {
    byte color;			//node's color
    int key;			//the key value
    RBTNode *left;		//the left child node
    RBTNode *right;		//the right child node
    RBTNode *parent;	//the parent node
};

void RBT_left_rotation(RBTRoot *root,RBTNode *X);
void RBT_right_rotation(RBTRoot *root,RBTNode *Y);
RBTRoot* RBT_create();
int RBT_insert_key(RBTRoot *root,int key);
RBTNode*  RBT_create_node(int key,RBTNode *parent,RBTNode *left,RBTNode *right);
void RBT_insert(RBTRoot *root,RBTNode *node);
void RBT_insert_fixup(RBTRoot *root,RBTNode *node);
void RBT_destroy(RBTNode *node);

#endif
