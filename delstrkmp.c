#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CalNext(char *str, int *next, int len)
{
    next[0] = -1; //next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
    int k = -1; //k初始化为-1
    int q;
    for (q = 1; q <= len-1; q++)
    {
        while (k > -1 && str[k + 1] != str[q]) //如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
        {
            k = next[k]; //往前回溯
        }
        if (str[k + 1] == str[q]) //如果相同，k++
        {
            k = k + 1;
        }
        next[q] = k; //这个是把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
    }
}

int DelStrKMP(char *str, int slen, char *ptr, int plen)
{
    //int *next = (int *)malloc(sizeof(int)*plen);
    int next[plen];
    CalNext(ptr, next, plen); //计算next数组
    int k = -1;
    char *st = NULL;
    char *tmp = NULL;
    //for (i = 0; i < slen; i++)
    while (*str)
    {
        while (k >-1 && ptr[k + 1] != *str) //ptr和str不匹配，且k>-1（表示ptr和str有部分匹配）
            k = next[k]; //往前回溯
        if (ptr[k + 1] == *str)
            k = k + 1;
        if (k == plen-1) //说明k移动到ptr的最末端
        {
            k = -1; //重新初始化，寻找下一个
            tmp = str;
            str -= (plen-1);
            st = str;
            tmp += 1;
            while (*st++ = *tmp++)
                ;
            continue;
        }
        str++;
    }
    return -1;  
}

int main()
{
	char str[] = "bacbababadababacambabacaddababacasdsd";
    char ptr[] = "ababaca";
    int slen = strlen(str);
    int plen = strlen(ptr);
    printf("before:%s\n", str);
    int a = DelStrKMP(str, slen, ptr, plen);
    printf("after:%s\n", str);

    return 0;
}
