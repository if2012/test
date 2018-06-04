#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CalNext(char *str, int *next, int len)
{
    next[0] = -1; //next[0]��ʼ��Ϊ-1��-1��ʾ��������ͬ�����ǰ׺������׺
    int k = -1; //k��ʼ��Ϊ-1
    int q;
    for (q = 1; q <= len-1; q++)
    {
        while (k > -1 && str[k + 1] != str[q]) //�����һ����ͬ����ôk�ͱ��next[k]��ע��next[k]��С��k�ģ�����kȡ�κ�ֵ��
        {
            k = next[k]; //��ǰ����
        }
        if (str[k + 1] == str[q]) //�����ͬ��k++
        {
            k = k + 1;
        }
        next[q] = k; //����ǰ����k��ֵ��������ͬ�����ǰ׺������׺��������next[q]
    }
}

int DelStrKMP(char *str, int slen, char *ptr, int plen)
{
    //int *next = (int *)malloc(sizeof(int)*plen);
    int next[plen];
    CalNext(ptr, next, plen); //����next����
    int k = -1;
    char *st = NULL;
    char *tmp = NULL;
    //for (i = 0; i < slen; i++)
    while (*str)
    {
        while (k >-1 && ptr[k + 1] != *str) //ptr��str��ƥ�䣬��k>-1����ʾptr��str�в���ƥ�䣩
            k = next[k]; //��ǰ����
        if (ptr[k + 1] == *str)
            k = k + 1;
        if (k == plen-1) //˵��k�ƶ���ptr����ĩ��
        {
            k = -1; //���³�ʼ����Ѱ����һ��
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
