/**
 输入一个正整数，转换为相应的字符串，保存在数组中。
 **/

#include <stdio.h>

void PrintDec(unsigned int num)
{
    if (num >= 10)
    {
        PrintDec(num /10);      
    }
    putchar(48 + num % 10); 
}

int PrintDec2Str(unsigned int num, char *p)
{
    int pos = 0;

    if (num >= 10)
    {
        pos = PrintDec2Str(num / 10, p);        
    }
    *(p + pos) = 48 + num % 10; 

    return pos + 1;
}

int main(void)
{
    int num = 0;
    char str[20] = {0xFF};

    printf("Please input a num:\n");

    scanf("%d",&num);

    str[PrintDec2Str(num, str)] = '\0';

    printf("The num has been converted to string.\n");

    puts(str);

    return 0;
}