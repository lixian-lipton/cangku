#include <stdio.h>
#include <stdbool.h>
bool request[11]={0},print,flag[11];
int x,level1,level2,load1=0,load2=0,run1=0,run2=0,time,n=0,turn=1;//x:万金油变量
int human[11][3],queue[11][2]={0},ele[11]={0};//ele[i]存储第i层的乘客上了几号电梯
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
int min(int a,int b)
{
    if(a>b)
        return b;
    return a;
}
int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
void debug()////////////////////////////
{
    printf("request:\n");
    for(int i=1;i<=10;i++){
        printf("%d ",request[i]);
    }
    printf("\nele:\n");
    for(int i=1;i<=10;i++){
        printf("%d ",ele[i]);
    }
    printf("\nhuman:\n");
    for(int i=1;i<=10;i++){
        printf("%d ",human[i][0]);
    }
    printf("\n");
    for(int i=1;i<=10;i++){
        printf("%d ",human[i][1]);
    }
    printf("\n");
    for(int i=1;i<=10;i++){
        printf("%d ",human[i][2]);
    }
    printf("\nrun1:%d  run2:%d\nlevel1:%d  level2:%d\n\n",run1,run2,level1,level2);
}
void state()
{
    printf("elevator1: %d %d %d  elevator2: %d %d %d\n",level1,time,load1,level2,time,load2);
}
int main() {
    printf("elevator\n");
    scanf("%d %d", &level1, &level2);
    printf("Please enter passengers' information (a person per line), and enter a '0 0 0' at the end.\n");
    while (1) {
        scanf("%d ", &x);
        scanf("%d %d", &human[x][1], &human[x][2]);
        queue[n + 1][0] = human[x][2];
        queue[n + 1][1] = x;
        if (x == 0)
            break;
        n++;
    }
    sort();
    //避免重复打印语句
    time = -1;
    while (n != 0) {                        //待考虑：如果电梯在同一层
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
            for (int i = 1; i <= 10; i++) {                              //先下
                if (human[i][1] == level1 && human[i][0] == 2 && ele[i] == 1) {
                    print = 1;
                    load1--;
                    n--;
                    human[i][0] = 0;
                    ele[i] = 0;
                }
                if (human[i][1] == level2 && human[i][0] == 2 && ele[i] == 2) {
                    print = 1;
                    level2--;
                    n--;
                    human[i][0] = 0;
                    ele[i] = 0;
                }
            }
            if (human[level1][0] == 1) {               //后上
                if (load1 < 4) {
                    load1++;
                    human[level1][0] = 2;
                    ele[level1] = 1;
                    request[human[level1][1]]=1;
                    print = 1;
                } else
                    request[level1] = 1;
            }
            if (human[level2][0] == 1 && load2 < 4) {
                if (load2 < 4) {
                    load2++;
                    human[level2][0] = 2;
                    ele[level2] = 1;
                    request[human[level2][1]]=1;
                    print = 1;
                } else
                    request[level2] = 1;
            }
        }
        if (run1 * run2 == 0) {
            if (run2 == 0 && run1 == 0) {
                for (int i = 1; i <= 10; i++) {
                    flag[i] = 0;      //flag用于标记乘客是否被响应，避免某些情况下两部电梯去接同一个人而有别人在等
                }
                for (int i = 1; i <= 9; i++) {
                    if (run1 == 0) {               //再次判定，是为了让电梯一旦响应了最近的就不再进行二次响应
                        x = min(10, level1 + i);
                        if (human[x][0] == 1 && flag[x] == 0) {
                            run1 = 1;
                            flag[x] = 1;
                        }
                        x = max(1, level1 - i);
                        if (human[x][0] == 1 && flag[x] == 0) {
                            run1 = -1;
                            flag[x] = 1;
                        }
                    }
                    if (run2 == 0) {
                        x = min(10, level1 + i);
                        if (human[x][0] == 1 && flag[x] == 0) {
                            run2 = 1;
                            flag[x] = 1;
                         }
                        x = max(1, level2 - i);
                        if (human[x][0] == 1 && flag[x] == 0) {
                            run2 = -1;
                            flag[x] = 1;
                        }
                    }
                }
            } else if (run1 == 0) {
                for (int i = 1; i <= 9; i++) {
                    x = min(10, level1 + i);
                    if (human[x][0] == 1)
                        if ((run2 == 1 && x > level2 && human[x][1] > x ||
                             run2 == -1 && x < level2 && human[x][1] < x) == false) {
                            run1 = 1;         //判断若另一部电梯可以接到，则不必响应
                            break;
                        }
                    x = max(1, level1 - i);
                    if (human[x][0] == 1)
                        if ((run2 == 1 && x > level2 && human[x][1] > x ||
                             run2 == -1 && x < level2 && human[x][1] < x) == false) {
                            run1 = -1;
                            break;
                        }
                }
            } else {
                for (int i = 1; i <= 9; i++) {
                    x = min(10, level2 + i);
                    if (human[x][0] == 1)
                        if ((run1 == 1 && x > level1 && human[x][1] > x ||
                             run1 == -1 && x < level1 && human[x][1] < x) == false) {
                            run2 = 1;
                            break;
                        }
                    x = max(1, level2 - i);
                    if (human[x][0] == 1)
                        if ((run1 == 1 && x > level1 && human[x][1] > x ||
                             run1 == -1 && x < level1 && human[x][1] < x) == false) {
                            run2 = -1;
                            break;
                        }
                }
            }
        } else {
            x = 0;
            for (int i = level1 + run1; i >= 1 && i <= 10; i += run1)
                if (human[i][1] == 1) {
                    x = 1;
                    break;
                }
            if (x == 0) {
                for (int i = 1; i <= 10; i++)
                    if (ele[i] == 1 && (human[i][1] - level1) * run1 > 0) {
                        x = 1;
                        break;
                    }
            }
            if (x == 0) {
                x = run1;
                run1 = 0;
                for (int i = 1; i <= 10; i++)
                    if (ele[i] == 1) {
                        run1 = x * -1;
                        break;
                    }
                if (run1 == 0) {
                    for (int i = level1 - x; i >= 1 && i <= 10; i -= x) {
                        if (human[i][1] == 1) {
                            run1 = x * -1;
                            break;
                        }
                    }
                }
            }
            x = 0;
            for (int i = level2 + run2; i >= 1 && i <= 10; i += run2)
                if (human[i][1] == 1) {
                    x = 1;
                    break;
                }
            if (x == 0) {
                for (int i = 1; i <= 10; i++)
                    if (ele[i] == 2 && (human[i][1] - level2) * run2 > 0) {
                        x = 1;
                        break;
                    }
            }
            if (x == 0) {
                x = run2;
                run2 = 0;
                for (int i = 1; i <= 10; i++)
                    if (ele[i] == 1) {
                        run2 = x * -1;
                        break;
                    }
                if (run2 == 0) {
                    for (int i = level2 - x; i >= 1 && i <= 10; i -= x) {
                        if (human[i][1] == 1) {
                            run2 = x * -1;
                            break;
                        }
                    }
                }
            }
        }
        if (print)
            state();
    }
    return 0;
}