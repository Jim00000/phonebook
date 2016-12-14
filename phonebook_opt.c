#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

#define NUM_BUCKETS 4

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], HashTable *ht)
{
    if(lastName != NULL && ht != NULL) {
        unsigned long hash = sdbm(lastName);
        unsigned int bucket = hash % NUM_BUCKETS;

        if(ht->buckets[bucket] == NULL) {
            return NULL;
        } else {
            entry *pHead = ht->buckets[bucket];
            while (pHead != NULL) {
                if (pHead->hash == hash )
                    return pHead;
                pHead = pHead->pNext;
            }

            return NULL;
        }
    }

    return NULL;
}

void append(char lastName[], HashTable *ht)
{
    if(lastName != NULL && ht != NULL) {

        /* calculate hash */
        unsigned long hash = sdbm(lastName);
        unsigned int bucket = hash % NUM_BUCKETS;

        if(ht->buckets[bucket] == NULL) {
            /* allocate a block of memory for this bucket */
            ht->buckets[bucket] = (entry *) malloc(sizeof(entry));
            /* check memory allocation */
            if(ht->buckets[bucket] == NULL) {
                fprintf(stderr, "allocating memory fails\n");
                exit(EXIT_FAILURE);
            }
        }

        entry *new_entry = (entry *) malloc(sizeof(entry));
        /* check memory allocation */
        if(new_entry == NULL) {
            fprintf(stderr, "allocating memory fails\n");
            exit(EXIT_FAILURE);
        }

        new_entry->pNext = ht->buckets[bucket];
        new_entry->hash = hash;

        ht->buckets[bucket] = new_entry;
    }

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

void free_HashTable(HashTable *hashTable)
{
    if(hashTable != NULL) {
        for(unsigned int i = 0; i<hashTable->buckets_num; i++) {
            free_entry(hashTable->buckets[i]);
        }
        free(hashTable->buckets);
        hashTable->buckets = NULL;
        free(hashTable);
        hashTable = NULL;
    }
}

unsigned long sdbm(const char *str)
{
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}