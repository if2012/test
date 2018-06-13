/**
 找出两个字符串中最大公共子字符串,如"abccade","dgcadde"的最大子串为"cad"
 如果存在多个，返回第一个
 **/
#include <stdio.h>
#include <string.h>
#include <assert.h>

void FindMaxCommonStr(const char *str1, const char *str2, char *max_str)
{
    int i, j, k;
    int max_pos = -1;
    int max_len = 0;

    assert(str1 != NULL && str2 != NULL);

    for (i = 0; i < strlen(str1); i++)
    {
        for (j = 0; j < strlen(str2); j++)
        {
            if (str1[i] == str2[j])
            {
                for (k = 1; (str1[i+k] == str2[j+k]) && str1[i+k] && str2[j+k]; k++)
                    ;
                if (k > max_len)
                {
                    max_len = k;
                    max_pos = i;
                }
            }
        }
    }

    if (max_pos == -1)
    {
        max_str[0] = '\0';
    }
    else
    {
        memcpy(max_str, str1+max_pos, max_len);
        max_str[max_len] = '\0';
    }
}

int main()
{
    char max_str[50] = {0xff};
    FindMaxCommonStr("yusdlkeersdf", "sdljfeersacv", max_str);

    printf("Result: %s\n", max_str);

    return 0;
}
