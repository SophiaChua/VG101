#include <stdio.h>

int digitSum(int num); 

int main()
{
    int num; 

    scanf("%d", &num);
    printf("%d\n", digitSum(num)); 
}

int digitSum(int num)
{
    int ans; 
    int mod; 
    
    if (num == 0)
        return 0;
    else if (num < 0)
    {
        num *= -1;
        mod = num % 10;
        ans = mod + digitSum(num / 10); 
        ans *= -1; 
        return ans; 
    }
    else 
    {
        mod = num % 10;
        ans = mod + digitSum(num / 10); 
        return ans; 
    }
}

