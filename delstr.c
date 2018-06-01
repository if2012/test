#include <stdio.h>

void DelStr(char *src, char *sub)
{
    char *st = src;
    char *s1 = NULL;
    char *s2 = NULL;

    if(st && sub) //判断字符串不为空
    {
        while (*st && *sub) //判断是否为字符串末尾
        {
            s1 = st;
            s2 = sub;
            while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
            {
                s1++;
                s2++;
            }
            if(*s2 == '\0')
            {
                while (*st++ = *s1++)
                    ;
                st = src;
                continue;

            }
            st++;
        }
    }
}

int main()
{
    char str1[] = "bbcdhellobc";
    char str2[] = "bc";

    DelStr(str1, str2);
    printf("Result:%s\n", str1);

    return 0;
}
