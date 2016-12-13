#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(unsigned long hash, entry *pHead)
{
    while (pHead != NULL) {
        if (pHead->hash == hash )
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if(lastName != NULL && e != NULL) {
        /* allocate memory for the new entry and put lastName */

        e->pNext = (entry *) malloc(sizeof(entry));
        /* check memory allocation */
        if(e->pNext == NULL) {
            fprintf(stderr, "allocating memory fails\n");
            exit(EXIT_FAILURE);
        }

        e = e->pNext;

        e->hash = sdbm(lastName);

        e->pNext = NULL;
    }

    return e;
}

void free_entry(entry *pHead)
{
    if(pHead != NULL) {
        entry *point_curr = pHead;
        while(point_curr != NULL) {
            entry *del_node = point_curr;
            point_curr = point_curr->pNext;
            free_Content(del_node->pContent);
            free(del_node);
            del_node = NULL;
        }
        pHead = NULL;
    }
}

void free_Content(Content *pHead)
{
    if(pHead != NULL) {
        free(pHead);
    }
    pHead = NULL;
}

unsigned long sdbm(const char *str)
{
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}