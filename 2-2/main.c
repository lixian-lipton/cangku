#include <stdio.h>
#include <stdbool.h>
bool request[11]={0},print,flag[10001];
int x,level1,level2,load1=0,load2=0,run1=0,run2=0,time,n=0,turn=1;//x:万金油变量
int human[11][1001][3],queue[10001][2]={0},ele[10001]={0};//ele[i]存储乘客上了几号电梯，i表示乘客的方法同queue
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
void state()
{
    printf("TIME:%d\nelevator1: LEVEL:%d LOAD:%d\nelevator2: LEVEL:%d LOAD:%d\n\n",time,level1,load1,level2,load2);
}
int main() {
    printf("elevator\n");
    scanf("%d %d", &level1, &level2);
    printf("Please enter passengers' information (a person per line), and enter a '0 0 0' at the end.\n");
    while (1) {
        scanf("%d ", &x);
        human[x][0][0]++;
        scanf("%d %d", &human[x][human[x][0][0]][1], &human[x][human[x][0][0]][2]);
        queue[n + 1][0] = human[x][human[x][0][0]][2];
        queue[n + 1][1] = human[x][0][0] * 100 + x;
        if (x == 0)
            break;
        n++;
    }
    sort();
    printf("TIME:0\nelevator1: LEVEL:%d LOAD:0\nelevator2: LEVEL:%d LOAD:0\n\n", level1, level2);
    time = -1;
    while (n != 0) {                        //待考虑：如果电梯在同一层
        print = 0;
        time++;
        level1 += run1;
        level2 += run2;
        for (int i = turn; queue[i][0] <= time && queue[i][1] % 100 != 0; i++, turn++) {   //先录入呼叫
            human[queue[i][1] % 100][queue[i][1] / 100][0] = 1;
            request[queue[i][1] % 100] = 1;
        }
        if (request[level1] == 1 || request[level2] == 1) {
            request[level1] = 0;
            request[level2] = 0;
            for (int i = 1; i <= 10; i++) {                              //先下
                for (int j = 1; j <= human[i][0][0]; j++) {
                    if (human[i][j][1] == level1 && human[i][j][0] == 2 && ele[j * 100 + i] == 1) {
                        print = 1;
                        load1--;
                        n--;
                        human[i][j][0] = 0;
                        ele[i + j * 100] = 0;
                    }
                    if (human[i][j][1] == level2 && human[i][j][0] == 2 && ele[i + j * 100] == 2) {
                        print = 1;
                        level2--;
                        n--;
                        human[i][j][0] = 0;
                        ele[i + j * 100] = 0;
                    }
                }
            }
            for (int i = 1; i <= human[level1][0][0]; i++) {
                if (human[level1][i][0] == 1) {               //后上
                    if (load1 < 4) {
                        load1++;
                        human[level1][i][0] = 2;
                        ele[level1 + i * 100] = 1;
                        request[human[level1][i][1]] = 1;
                        print = 1;
                    } else
                        request[level1] = 1;
                }
            }
            for (int i = 1; i <= human[level1][0][0]; i++) {
                if (human[level2][i][0] == 1) {
                    if (load2 < 4) {
                        load2++;
                        human[level2][i][0] = 2;
                        ele[level2 + i * 100] = 1;
                        request[human[level2][i][1]] = 1;
                        print = 1;
                    } else
                        request[level2] = 1;
                }
            }
        }
        if (run1 * run2 == 0) {
            if (run2 == 0 && run1 == 0) {
                for (int i = 1; i <= 10; i++) {
                    for (int j = 1; j <= human[i][0][0]; j++) {
                        flag[i + j * 100] = 0;      //flag用于标记乘客是否被响应，避免某些情况下两部电梯去接同一个人而有别人在等
                    }
                }
                for (int i = 1; i <= 9; i++) {
                    if (run1 == 0) {               //再次判定，是为了让电梯一旦响应了最近的就不再进行二次响应
                        x = min(10, level1 + i);
                        for (int j = 1; j <= human[x][0][0]; j++) {
                            if (human[x][j][0] == 1 && flag[x + j * 100] == 0) {
                                run1 = 1;
                                flag[x + j * 100] = 1;
                            }
                        }
                        x = max(1, level1 - i);
                        for (int j = 1; j <= human[x][0][0]; j++) {
                            if (human[x][j][0] == 1 && flag[x + j * 100] == 0) {
                                run1 = -1;
                                flag[x + j * 100] = 1;
                            }
                        }
                    }
                    if (run2 == 0) {
                        x = min(10, level1 + i);
                        for (int j = 1; j <= human[x][0][0]; j++) {
                            if (human[x][j][0] == 1 && flag[x + j * 100] == 0) {
                                run2 = 1;
                                flag[x + j * 100] = 1;
                            }
                        }
                        x = max(1, level2 - i);
                        for (int j = 1; j <= human[x][0][0]; j++) {
                            if (human[x][j][0] == 1 && flag[x + j * 100] == 0) {
                                run2 = -1;
                                flag[x + j * 100] = 1;
                            }
                        }
                    }
                }
            } else if (run1 == 0) {
                for (int i = 1; i <= 9; i++) {//
                    x = min(10, level1 + i);
                    for (int j = 1; j <= human[x][0][0]; j++) {
                        if (human[x][j][0] == 1)
                            if ((run2 == 1 && x > level2 && human[x][j][1] > x ||
                                 run2 == -1 && x < level2 && human[x][j][1] < x) == false) {
                                run1 = 1;         //判断若另一部电梯可以接到，则不必响应
                                break;
                            }
                    }
                    x = max(1, level1 - i);
                    for (int j = 1; j <= human[x][0][0]; j++) {
                        if (human[x][j][0] == 1)
                            if ((run2 == 1 && x > level2 && human[x][j][1] > x ||
                                 run2 == -1 && x < level2 && human[x][j][1] < x) == false) {
                                run1 = -1;
                                break;
                            }
                    }
                }
            } else {
                for (int i = 1; i <= 9; i++) {
                    x = min(10, level2 + i);
                    for (int j = 1; j <= human[x][0][0]; j++) {
                        if (human[x][j][0] == 1)
                            if ((run1 == 1 && x > level1 && human[x][j][1] > x ||
                                 run1 == -1 && x < level1 && human[x][j][1] < x) == false) {
                                run2 = 1;
                                break;
                            }
                    }
                    x = max(1, level2 - i);
                    for (int j = 1; j <= human[x][0][0]; j++) {
                        if (human[x][j][0] == 1)
                            if ((run1 == 1 && x > level1 && human[x][j][1] > x ||
                                 run1 == -1 && x < level1 && human[x][j][1] < x) == false) {
                                run2 = -1;
                                break;
                            }
                    }
                }
            }
        } else {
            x = 0;             //x=1时，保持现有方向；否则考虑停止或转向
            for (int i = level1 + run1; i >= 1 && i <= 10; i += run1)
                for (int j = 1; j <= human[i][0][0]; j++) {
                    if (human[i][j][0] == 1) {                      //前方有人等候
                        if ((i - level2) * run2 > 0 && (human[i][j][1] - i) * run2 > 0) {//如果另一部电梯可以接应，则不必响应
                            continue;
                        } else {
                            x = 1;
                            break;
                        }
                    }
                }
            if (x == 0) {
                for (int i = 1; i <= 10; i++)
                    for (int j = 1; j <= human[i][0][0]; j++) {
                        if (ele[i + j * 100] == 1 && (human[i][j][1] - level1) * run1 > 0) {
                            x = 1;                           //有乘客需要在前方下电梯,x=1
                            break;
                        }
                    }
            }
            if (x == 0) {                      //不保持现有运行方向
                x = run1;
                run1 = 0;
                for (int i = 1; i <= 10; i++)
                    for (int j = 1; j <= human[i][0][0]; j++) {
                        if (ele[i + j * 100] == 1) {          //还有乘客在电梯上，转向继续运行
                            run1 = x * -1;
                            break;
                        }
                    }
                if (run1 == 0) {                //仍为0，意味着没有乘客在电梯上了
                    for (int i = level1 - x; i >= 1 && i <= 10; i -= x) {
                        for (int j = 1; j <= human[i][0][0]; j++) {
                            if (human[i][j][1] == 1) {             //反向检索是否有等待中乘客
                                run1 = x * -1;
                                break;
                            }
                        }
                    }
                }
            }
            x = 0;
            for (int i = level2 + run2; i >= 1 && i <= 10; i += run2)
                for (int j = 1; j <= human[i][0][0]; j++) {
                    if (human[i][j][0] == 1) {
                        if ((i - level1) * run1 > 0 && (human[i][j][1] - i) * run1 > 0) {
                            continue;
                        } else {
                            x = 1;
                            break;
                        }
                    }
                }
            if (x == 0) {
                for (int i = 1; i <= 10; i++)
                    for (int j = 1; j <= human[i][0][0]; j++) {
                        if (ele[i + j * 100] == 2 && (human[i][j][1] - level2) * run2 > 0) {
                            x = 1;
                            break;
                        }
                    }
            }
            if (x == 0) {
                x = run2;
                run2 = 0;
                for (int i = 1; i <= 10; i++)
                    for (int j = 1; j <= human[i][0][0]; j++) {
                        if (ele[i + j * 100] == 1) {
                            run2 = x * -1;
                            break;
                        }
                    }
                if (run2 == 0) {
                    for (int i = level2 - x; i >= 1 && i <= 10; i -= x) {
                        for (int j = 1; j <= human[i][0][0]; j++) {
                            if (human[i][j][1] == 1) {
                                run2 = x * -1;
                                break;
                            }
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