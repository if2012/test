/**
字符串为空串或空指针.
字符串含有非0到9的字符.
特别注意字符串转换到int值,要考虑溢出的问题,正整数的最大值是0x7FFFFFFF,负数的最小值是0x80000000.
 **/
#include<stdio.h>
#include<string.h>

typedef enum bool{false, true}bool;

int StrToInt(const char *str, int *nInt)
{
	if (str == NULL)
	{
		printf("空指针\n");
		return  false;
	}
	else if (str == "")
	{
		printf("空串\n");
		return false;
	}
	else if ((strcmp(str,"+") == 0) || (strcmp(str,"-") == 0))
	{
		printf("字符串输入无效\n");
		return false;
	}
	else
	{
		const char *p = str;
		bool isFirst = true; //标记是否为字符串的第一个字符
		bool hasMinus = false; //标记字符串的第一个字符是否是负号
		*nInt = 0;
		while (*p != '\0')
		{
			if (isFirst && (*p) == '-' )
			{
				hasMinus = true;
				p++;
				continue;
			}
			else if (isFirst && (*p) == '+')
			{
				p++;
				continue;
			}
			if ((*p) >= '0' && (*p) <= '9')
			{
				//*nInt = *nInt*10 + *p-'0';
				if ((!hasMinus && (*p - '0') > (2147483647 - *nInt*10)) || (hasMinus && -(*p - '0') > (-2147483648 + *nInt*10)))
				{
					return 2;
				}
				*nInt = *nInt*10 + *p-'0';
				p++;
			}
			else
			{
				return 3;
			}
		}
		if (hasMinus)
		{
			*nInt = (-1) * (*nInt);
		}
		return true;
	}
}

int main()
{
	int nInt = 0;
	char str[33] = {0xff};

	printf("Please input a integer:\n");
	scanf("%s", str);

	int val = StrToInt(str, &nInt);

	if (val == 2)
	{
		printf("字符串数值溢出，输入无效!\n");
	}
	else if (val == 3)
	{
		printf("字符串中包含有非数字的字符，不能转换为数字\n");
	}
	else
	{
		printf("num = %d\n", nInt);
	}

	return 0;
}
