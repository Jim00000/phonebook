#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long djb2(unsigned char *str);
unsigned long sdbm(unsigned char *str);
unsigned long loselose(unsigned char *str);
double diff_time(struct timespec *start,struct timespec *end);

int main(void)
{
    char* str = "1234567890";
    struct timespec start,end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    djb2((unsigned char *)str);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("djb2 %.9lf seconds \n",diff_time(&start,&end));

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sdbm((unsigned char *)str);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("sdbm %.9lf seconds \n",diff_time(&start,&end));

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    loselose((unsigned char *)str);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("loselose %.9lf seconds \n",diff_time(&start,&end));


    return 0;
}

unsigned long djb2(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

unsigned long sdbm(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

unsigned long loselose(unsigned char *str)
{
    unsigned int hash = 0;
    int c;

    while ((c = *str++))
        hash += c;

    return hash;
}

double diff_time(struct timespec *start,struct timespec *end)
{
    double time = 0.0;
    time += end->tv_sec - start->tv_sec;
    time += (end->tv_nsec - start->tv_nsec) / 1000000000.0;
    return time;
}