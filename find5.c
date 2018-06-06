#include <stdio.h>

#define NUM 1000

int find5(int num)
{
    int ret=0;
    while (num%5 == 0)
    {
        num /= 5;
        ret++;
    }
    return ret;
}
int main()
{
    int result = 0;
    int i;
    for (i = 5; i <= NUM; i += 5)
    {
        result += find5(i);
    }
    printf("the total zero number is %d\n", result);

    return 0;
} 
