#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"

/* original version */
entry *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    if(e->pNext == NULL) {
        fprintf(stderr, "allocating memory fails\n");
        exit(EXIT_FAILURE);
    }
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

void free_entry(entry *pHead)
{
    if(pHead != NULL) {
        entry *point_curr = pHead;
        while(point_curr != NULL) {
            entry *del_node = point_curr;
            point_curr = point_curr->pNext;
            free(del_node);
            del_node = NULL;
        }
        pHead = NULL;
    }
}
