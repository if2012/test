/**
求2~2000的所有的素数，有足够的内存，要求尽量快。
**/

#include <stdio.h>
#include <stdlib.h>

typedef enum bool{false, true}bool;

int findvalue[2000]={2};  
static int findx=1;  
bool adjust(int value)
{  
	int i;

	if (value==2)  
		return true;  

	for (i = 0;i < findx;i++)  
	{  
		if (value%findvalue[i] == 0)  
			return false;  
	}  
	findvalue[findx++]=value;  
	return true;  
}  
int main()
{  
	int i;
	for (i = 2;i < 2000;i++)  
		adjust(i);  
	for (i = 0;i < findx;i++)  
		printf("%d\n", findvalue[i]);  
	
	return 0;
}
