/**
 输入一个正整数，转换为相应的字符串，保存在数组中。
 **/

#include <stdio.h>

int Dec2Str(unsigned int num, char *p)
{
    int pos = 0;
#if 0
    if (num >= 10)
    {
        pos = Dec2Str(num / 10, p);        
    }
    *(p + pos) = '0' + num % 10; 

    return pos + 1;
#elseif
	if (num >= 10)
	{
		Dec2Str(num / 10, p);
	}
	*p++ = '0' + num % 10;
	*p = '\0';
#endif
}

int main(void)
{
    int num = 0;
    char str[20] = {0xFF};

    printf("Please input a num:\n");

    scanf("%d",&num);

    //str[Dec2Str(num, str)] = '\0';
	Dec2Str(num, str);

    printf("The num has been converted to string.\n");

    puts(str);

    return 0;
}