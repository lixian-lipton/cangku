#include <stdio.h>
#include <math.h>
int a,b,c;
int main()
{
    freopen("1-2.in","r",stdin);
    freopen("1-2.out","w",stdout);
    scanf("elevator %d %d %d",&a,&b,&c);
    printf("floor time people\n");
    printf("%d %d %d\n%d %d %d\n%d %d %d",a,0,0,b,abs(a-b),1,c,abs(a-b)+abs(b-c),0);
    fclose(stdin);
    fclose(stdout);
    return 0;
}