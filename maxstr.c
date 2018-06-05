/**
 * 在一个字符串中找到可能的最长的子字符串，且该字符串是由同一字符组成的。
 * */
#include <stdio.h>
#include <string.h>

int GetMaxStr(char *str, int *maxlen)
{
    int L = 1;
    int  maxpos = 1;
    *maxlen = 1;
    int i = 0;
    while (str[i])
    { 
        if (str[i] == str[i+1])
        {
            L++;
        }
        else
        {
            if (L > *maxlen)
            {
               *maxlen = L;
                maxpos = i+2-L;

            }
            L = 1;
        }   

        ++i;
    }
    return maxpos;
}

int main() 
{
    char s[] = "ddddddd0000000001112236543";
    int len,pos;
    pos = GetMaxStr(s, &len);
    printf("pos = %d,len = %d\n",pos,len);
    return 0;
}
