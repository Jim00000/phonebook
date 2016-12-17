#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define RED 0
#define BLACK 1

typedef unsigned char byte;

typedef struct __PHONE_BOOK_ENTRY entry;
typedef struct __PHONE_BOOK_CONTENT Content;
typedef struct __PHONE_BOOK_HASH_TABLE HashTable;
typedef struct __RED_BLACK_TREE_Root RBTRoot;
typedef struct __RED_BLACK_TREE_Node RBTNode;

struct __PHONE_BOOK_ENTRY {
    unsigned long hash;
    entry *pNext;
    Content *pContent;
};

struct __PHONE_BOOK_CONTENT {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
};

struct __PHONE_BOOK_HASH_TABLE {
    unsigned int buckets_num;
    RBTRoot **buckets;
};

struct __RED_BLACK_TREE_Root {
    RBTNode *node;
};

struct __RED_BLACK_TREE_Node {
    byte color;			//node's color
    unsigned long key;	//the key value
    Content *pContent;	//the phonebook data
    RBTNode *left;		//the left child node
    RBTNode *right;		//the right child node
    RBTNode *parent;	//the parent node
};

RBTNode *findName(char lastName[], HashTable *ht);
void append(char lastName[], HashTable *e);
unsigned long sdbm(const char *str);
void free_entry(entry *pHead);
void free_Content(Content *pHead);
void free_HashTable(HashTable *hashTable);

/* Red Black Tree declaration */
void RBT_left_rotation(RBTRoot *root,RBTNode *X);
void RBT_right_rotation(RBTRoot *root,RBTNode *Y);
RBTRoot* RBT_create();
int RBT_insert_key(RBTRoot *root,unsigned long key);
RBTNode*  RBT_create_node(unsigned long key,RBTNode *parent,RBTNode *left,RBTNode *right);
void RBT_insert(RBTRoot *root,RBTNode *node);
void RBT_insert_fixup(RBTRoot *root,RBTNode *node);
void RBT_destroy(RBTNode *node);


#endif
