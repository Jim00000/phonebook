#include <stdio.h>

#include "fuzzy_search.h"

int main(void)
{
    char *sample = "McDonald";
    char *str1 =   "MacDonald";
    char *str2 =   "McDonalds";

    float percent = similarity(sample,str1);
    printf("Similarity is %f\n",percent);
    percent = similarity(sample,str2);
    printf("Similarity is %f\n",percent);

    return 0;
}
