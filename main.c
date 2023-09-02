#include <stdio.h>
#include <math.h>
int a,b,c;
int ans1,ans2;
int main()
{
    scanf("%d %d %d",&a,&b,&c);
    ans1=fabs(a-c);
    ans2=ans1+fabs(a-b);
    printf("%d %d %d\n%d %d %d\n%d %d %d\n",c,0,0,a,ans1,1,b,ans2,0);
    return 0;
}