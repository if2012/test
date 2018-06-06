#include <stdio.h>

int MyStrcmp(char *source, char *dest)
{
    if (source == NULL || dest == NULL)
        return -1;

    while (*source++ && *dest++)
    {
        if (*source > *dest)
            return 1;
        else if (*source < *dest)
            return -1;
    }
    
    if (!*source && !*dest)
        return 0;
    else if (*source)
        return 1;
    else
        return -1;
}

int main()
{
    char source[50]  = {0xff};
    char dest[50] = {0xff};

    scanf("%s", source);
    scanf("%s", dest);

    printf("result:%d\n", MyStrcmp(source, dest));

    return 0;
}
