#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

typedef struct __PHONE_BOOK_ENTRY entry;
typedef struct __PHONE_BOOK_CONTENT Content;
typedef struct __PHONE_BOOK_HASH_TABLE HashTable;

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
    entry **buckets;
};

entry *findName(char lastName[], HashTable *ht);
void append(char lastName[], HashTable *e);
unsigned long sdbm(const char *str);
void free_entry(entry *pHead);
void free_Content(Content *pHead);
void free_HashTable(HashTable *hashTable);

#endif
