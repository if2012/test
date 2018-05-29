/**
  输入一个字符串，转换为相应的正整数
 **/

#include <stdio.h>

int Str2Num(char *pstr, unsigned int *num)
{
	while (*pstr != '\0')
	{
		if (*pstr > '9' || *pstr < '0')
		{
			return 1;
		}
		/* 判断正整数是否溢出 */
		if ((*pstr - '0') > (4294967295 - *num*10))
			return 2;
		*num *= 10;
		*num += *pstr - '0';
		pstr++;
	}

	return 0;
}

int main(void)
{
	char str[20] = {0xFF};
	unsigned int num = 0;

	printf("Please input a integer:\n");
	scanf("%s",str);

	int val = Str2Num(str, &num);

	if (val == 1)
	{
		printf("输入不为数字!\n");
	}
	else if (val == 2)
	{
		printf("正整数溢出!\n");
	}
	else
	{
		printf("num = %u\n", num);
	}

	return 0;
}
