#include <stdio.h>


int main() {

    char const *ptr1 = "ABC";
    char * const ptr2 = "BAC";

    const char *s = "123456";

    const char * const  ptr3 = "CAB";

    ptr1 = s;
    *ptr1 = *s;

    ptr2 = s;
    *ptr2 = *s;

    ptr3 = s;
    *ptr3 = *s;

    return 0;
}