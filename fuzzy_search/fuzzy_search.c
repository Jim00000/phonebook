#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fuzzy_search.h"

/* function prototype */
inline void print_array(const int rowsz,const int colsz,const int ary[][colsz]) __attribute__((always_inline));

inline int edit_distance(const int left,const int up,const int upperleft,const char ch1,const char ch2) __attribute__((always_inline));

inline int max(const int a,const int b) __attribute__((always_inline));

inline int min(const int a,const int b) __attribute__((always_inline));

/* function definition */
inline void print_array(const int rowsz,const int colsz,const int ary[][colsz])
{
    if(ary != NULL && rowsz >= 1 && colsz >= 1) {
        for( int i = 0 ; i < rowsz ; i++ ) {
            printf("[ ");
            for( int j = 0 ; j < colsz ; j++ ) {
                printf("%d,",ary[i][j]);
            }
            printf("\b ]\n");
        }
    } else {
        fprintf(stderr,"error:print array fails\n");
    }
}

inline int edit_distance(const int left,const int up,const int upperleft,const char ch1,const char ch2)
{
    const int case1 = left + 1;
    const int case2 = up + 1;
    const int case3 = upperleft + ((ch1 == ch2)? 0 : 1);
    return min(case1,min(case2,case3));
}

inline int max(const int a,const int b)
{
    return (a >= b) ? a : b;
}

inline int min(const int a,const int b)
{
    return (a >= b) ? b : a;
}

int levenshtein(const char *str1,const char *str2)
{
    int rowsize = strlen(str1) + 1;
    int columnsize = strlen(str2) + 1;
    int table[rowsize][columnsize];

    // fill initial values
    memset(table,0,rowsize * columnsize * sizeof(int) );
    for(int i=0; i<columnsize; i++)
        table[0][i] = i;
    for(int j=1; j<rowsize; j++)
        table[j][0] = j;

    // calculate edit distance
    for(int i=1; i<rowsize; i++) {
        for(int j=1; j<columnsize; j++) {
            table[i][j] = edit_distance(table[i][j-1],table[i-1][j],table[i-1][j-1],str1[i-1],str2[j-1]);
        }
    }

    // debug:show that array
    // print_array(rowsize,columnsize,table);
    return table[rowsize - 1][columnsize - 1];
}

float similarity(const char* str1,const char* str2)
{
    int edit_distance = levenshtein(str1,str2);
    printf("edit_distance is %d\n",edit_distance);
    printf("max is %d\n",max(strlen(str1),strlen(str2)));
    return 1.0f - (float)edit_distance / (float)max(strlen(str1),strlen(str2));
}
