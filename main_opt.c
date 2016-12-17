#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#if defined(__linux__) & defined(MEMLEAK)
#include <mcheck.h>
#endif

#define NUM_BUCKETS 32
#define LOG_FILE "opt.txt"
#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(void)
{

#if defined(__linux__) & defined(MEMLEAK)
    setenv("MALLOC_TRACE", "./memleak.log",1);
    mtrace();
#endif

    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        fprintf(stderr,"cannot open the file\n");
        exit(EXIT_FAILURE);
    }

    /* build the hash table */
    HashTable *hashTable = (HashTable *) malloc(sizeof(HashTable));

    /* check memory allocation */
    if(hashTable == NULL) {
        fprintf(stderr, "allocating memory fails\n");
        exit(EXIT_FAILURE);
    }

    hashTable->buckets_num = NUM_BUCKETS;
    hashTable->buckets = (RBTRoot **) malloc(NUM_BUCKETS * sizeof(RBTRoot *));

    /* check memory allocation */
    if(hashTable->buckets == NULL) {
        fprintf(stderr, "allocating memory fails\n");
        exit(EXIT_FAILURE);
    }

    printf("size of entry : %lu bytes\n", sizeof(entry));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) hashTable, (char *) hashTable + sizeof(hashTable));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        append(line,hashTable);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";

    assert(findName(input, hashTable) &&
           "Did you implement findName() in " IMPL "?");
    assert(1 == (findName(input, hashTable)->key == sdbm(input) ));


#if defined(__GNUC__)
    __builtin___clear_cache((char *) hashTable, (char *) hashTable + sizeof(hashTable));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, hashTable);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    FILE *output = NULL;
    output = fopen(LOG_FILE, "a");

    /* check file status */
    if(output == NULL) {
        fprintf(stderr,"open file %s error\n",LOG_FILE);
        exit(EXIT_FAILURE);
    }

    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    /* free linklist memory */
    free_HashTable(hashTable);

    return 0;
}
