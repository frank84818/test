#include <stdio.h>
// #include <cstdlib>
#include <stdlib.h>
#include "string.h"
#include <stddef.h>

int a[3];
struct {double v[3]; double length;} b[17];
int calendar[12][31];


int main() {

    char *s= "123";
    char *r= "456";
    
    char *c = (char *)malloc((strlen(s)+strlen(r))*sizeof(char) + 1);
    if(!c) exit(1);

    strcpy(c,s);
    strcat(c,r);


    printf("%s\n", c);

    free(c);
    c = NULL;


}