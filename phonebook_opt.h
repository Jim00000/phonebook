#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

typedef struct __PHONE_BOOK_ENTRY entry;
typedef struct __PHONE_BOOK_CONTENT Content;

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

entry *findName(unsigned long hash, entry *pHead);
entry *append(char lastName[], entry *e);
void free_entry(entry *pHead);
void free_Content(Content *pHead);
unsigned long sdbm(const char *str);

#endif
