#include <stdio.h>
#include <stdbool.h>
bool request[11]={0},print;
int level1,level2,load1=0,load2=0,run1=0,run2=0,time,n=0,turn=1;
int human[11][3],queue[11][2]={0};
void sort()
{
    int x;
    for(int i=n-1;i>=1;i--)
        for(int j=1;j<=i;j++)
            if(queue[j][0]>queue[j+1][0]) {
                x = queue[j][0];
                queue[j][0] = queue[j + 1][0];
                queue[j + 1][0] = x;
                x = queue[j][1];
                queue[j][1] = queue[j + 1][1];
                queue[j + 1][1] = x;
            }
}
void status()
{
    printf("elevator1: %d %d %d  elevator2: %d %d %d",level1,time,load1,level2,time,load2);
}
int main()
{
    printf("elevator\n");
    scanf("%d %d",&level1,&level2);
    printf("Please enter passengers' information (a person per line), and enter a '0 0 0' at the end.\n");
    while(1) {
        int x;
        scanf("%d ", &x);
        scanf("%d %d", &human[x][1], human[x][2]);
        queue[n + 1][0] = human[x][2];
        queue[n + 1][1] = x;
        if (x == 0)
            break;
        n++;
    }
    sort();
    //避免重复打印语句
    time=-1;
    while(n!=0) {                        //待考虑：如果电梯在同一层
        print = 0;
        time++;
        level1 += run1;
        level2 += run2;
        for (int i = turn; queue[i][0] <= time && i <= 10; i++, turn++) {   //先录入呼叫
            human[queue[i][1]][0] = 1;
            request[queue[i][1]] = 1;
        }
        if (request[level1] == 1 || request[level2] == 1) {
            request[level1] = 0;
            request[level2] = 0;
            for (int i = 1; i <= 10; i++) {                            //先下
                if (human[i][1] == level1 && human[i][0] == 2) {
                    print = 1;
                    load1--;
                    n--;
                    human[i][0] = 0;
                }
                if (human[i][1] == level2 && human[i][0] == 2) {
                    print = 1;
                    level2--;
                    n--;
                    human[i][0] = 0;
                }
            }
            if (human[level1][0] == 1) {
                if (load1 < 4) {
                    load1++;
                    human[level1][0] = 2;
                    print = 1;
                } else
                    request[level1] = 1;
            }
            if (human[level2][0] == 1 && load2 < 4) {
                if (load2 < 4) {
                    load2++;
                    human[level2][0] = 2;
                    print = 1;
                } else
                    request[level2] = 1;
            }
        }
        if(run1*run2==0){
            if(run2==0&&run1==0){

            }
            else{

            }
        }
        else{
            
        }
        if (print)
            status();
    }
}
