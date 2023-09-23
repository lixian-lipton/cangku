#include <stdio.h>
#include <stdbool.h>
int run=0,human[11][1001][3]={0},x;//run=1/0/-1，为运行方向，human[i][j][1]为第j位从i层出发的乘客目的地，human[i][j][2]为加入时间
int level,time,load=0,n=0;//              human[i][j][0]表示状态，0为不存在/已到达，1为等待，2在电梯上
int up=0,down=0,queue[10001][2],turn=1;//queue[i][0]存时间，queue[i][1]存人,up down表示上下侧请求楼层数量
bool request[11]={0},flag=0,print;// queue[i][j]中，i是一个多位数，其中末2位表示起始楼层，前面的数字表示此人是该楼层第几位乘客
//request[i]表示第i层是否有请求
void sort() {
    for (int i = n - 1; i >= 1; i--)
        for (int j = 1; j <= i; j++)
            if (queue[j][0] > queue[j + 1][0]) {
                x = queue[j][0];
                queue[j][0] = queue[j + 1][0];
                queue[j + 1][0] = x;
                x = queue[j][1];
                queue[j][1] = queue[j + 1][1];
                queue[j + 1][1] = x;
            }
}
void requ(int lev)//lev为请求楼层，要确保lev!=level时才执行它
{
    if (lev > level && request[lev] == 0) {
        up++;
    }
    if (lev < level && request[lev] == 0) {
        down++;
    }
    request[lev] = 1;
}
void state() {
    printf("LEVEL:%d  TIME:%d  LOAD:%d\n", level, time, load);
}
int main() {
    printf("elevator\n");
    scanf("%d", &level);
    printf("Please enter passengers' information (a person per line), and enter a '0 0 0' at the end.\n");
    printf("Enter in order:starting floor, destination, time\n ");
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 1001; j++)
            for (int k = 0; k < 3; k++)
                human[i][j][k] = 0;
    while (1) {
        scanf("%d ", &x);
        human[x][0][0]++;              //human[i][0][0]存储第i层共有多少乘客
        scanf("%d %d", &human[x][human[x][0][0]][1], &human[x][human[x][0][0]][2]);
        queue[n + 1][0] = human[x][human[x][0][0]][2];
        queue[n + 1][1] = human[x][0][0] * 100 + x;
        if (x == 0)
            break;
        n++;
    }
    sort();
    for (int i = 1; queue[i][0] == 0; i++)
        if (queue[i][1] % 100 == level)
            flag = 1;
    if (flag == 0)
        printf("LEVEL:%d  TIME:0  LOAD:0\n", &level);//如果正好有人再起始时刻初始楼层上电梯，则不再重复输出（下面循环中会输出）
    flag = 0;
    time = -1;
    while (n != 0) {
        time++;
        level += run;
        if (run == 0)               //跳过等待
            time = queue[turn][0];
        if (flag) {               //flag负责处理一个遗留问题，具体意义见循环靠后部分注释
            if (run == 1) {
                down++;
            }
            else {
                up++;
            }
        }
        flag = 0;
        print = 0;                        //print判断是否打印电梯状态
        if (request[level]) {
            switch (run) {
                case 1:
                    up--;
                    break;
                case -1:
                    down--;
                    break;
            }
            for (int i = 1; i <= 10; i++)             //先下
                for (int j = 1; j <= human[i][0][0]; j++)
                    if (human[i][j][1] == level && human[i][j][0] == 2) {
                        load--;
                        n--;
                        print = 1;
                        human[i][j][0] = 0;
                    }
        }
        for (int i = turn; queue[i][0] <= time && queue[i][1]%100 != 0; i++, turn++)//从turn开始防止有人下了又上，循环防止多人同时按下按键
        {
            human[queue[i][1] % 100][queue[i][1] / 100][0] = 1;
            if (queue[i][1] != level) {             //若按键的楼层和电梯所在楼层不一致
                requ(queue[i][1] % 100);
            }
        }
        for (int i = 1; i <= human[level][0][0]; i++)
            if (human[level][i][0] == 1) {                         //后上
                if (load < 4) {
                    load++;
                    requ(human[level][i][1]);
                    human[level][i][0] = 2;
                    print = 1;
                } else {                        //要上电梯却满载荷，这是唯一一种无法当场解决的请求
                    flag = 1;                   //将在下次循环做有关处理，具体如循环开头flag部分
                }
            }
        request[level] = flag;             //flag的作用，标记该楼层的所有请求是否都已被处理
        if (print == 1)
            state();
        if (up == 0 && down == 0)                         //开始判断电梯接下来运动方向
            run = 0;
        else if (up != 0 && down == 0)
            run = 1;
        else if (up == 0 && down != 0)
            run = -1;
        else if (run == 0) {                         //电梯停止时，往更近的请求一端运行
            for (int i = 1; i <= 10; i++) {
                if (request[level + i]) {
                    run = 1;
                    break;
                } else if (request[level - i]) {
                    run = -1;
                    break;
                }
            }
        }
    }
    return 0;
}