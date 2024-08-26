#include <stdio.h>

void PrintNum()
{
    unsigned int i = 0x80;
    printf("%d, ", i);
    printf("%d, ", i << 1);
}

int main()
{
    PrintNum();
    return 0;
}