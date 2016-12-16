#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

#define ARRAYLENGTH(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

int main(void)
{
    int keys[] = {10,40,30,60,90,70,20,50,80};
    RBTRoot *root = RBT_create();

    for(size_t i=0; i<ARRAYLENGTH(keys); i++) {
        RBT_insert_key(root,keys[i]);
    }

    //printf("%d\n",root->node->key);
    //printf("%d\n",root->node->left->key);
    //printf("%d\n",root->node->right->key);

    RBT_destroy(root->node);
    free(root);
    return 0;
}
