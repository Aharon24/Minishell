#include <stdio.h>

int main(void)
{
    char *ptr = NULL;
    printf("%c\n", ptr[0]);  // попытка прочитать по нулевому указателю — segfault
    return 0;
}

