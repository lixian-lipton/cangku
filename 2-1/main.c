#include <stdio.h>
#include <stdbool.h>
int run=0,human[11][3]={0},x;//run=1/0/-1，为运行方向，human[i][1]为从i层出发的乘客目的地，human[i][2]为加入时间
int level,time,load=0,n=0;//              human[i][0]表示状态，0为不存在/已到达，1为等待，2在电梯上
int up=0,down=0,queue[12][2],turn=1;//queue[i][0]存时间，queue[i][1]存人（用出发楼层代表）,up down表示上下侧请求楼层数量
bool request[11]={0},flag=0;//request[i]表示第i层是否有请求
void sort()
{
    int x;
    for(int i=n-1;i>=1;i--)
        for(int j=1;j<=i;j++)
            if(queue[j][0]>queue[j+1][0]){
                x=queue[j][0];
                queue[j][0]=queue[j+1][0];
                queue[j+1][0]=x;
                x=queue[j][1];
                queue[j][1]=queue[j+1][1];
                queue[j+1][1]=x;
            }
}
void requ(int lev)//要确保lev!=level时才执行它
{
    if(lev>level&&request[lev]==0)
        up++;
    if(lev<level&&request[lev]==0)
        down++;
    request[lev]=1;
}
void status()
{
    printf("%d %d %d\n",level,time,load);
}
int main()
{
    printf("elevator\n");
    scanf("%d",&level);
    printf("Please enter passengers' information (a person per line), and enter a '0 0 0' at the end.\n");
    while(1){
        scanf("%d ",&x);
        scanf("%d %d",&human[x][1],&human[x][2]);
        queue[n+1][0]=human[x][2];
        queue[n+1][1]=x;
        if(x==0)
            break;
        n++;
    }
    if(human[level][0]==0&&human[level][1]==0)//避免重复打印
        printf("%d 0 0\n",level);
    sort();
    time=-1;
    while(n!=0){
        time++;
        if(run==0)               //跳过等待
            time=queue[turn][0];
        if(flag){               //flag意义见下文
            if(run==1)
                down++;
            else
                up++;
        }
        level+=run;
        flag=0;
        if(request[level]){
            switch (run){
                case 1:
                    up--;
                    break;
                case -1:
                    down--;
                    break;
            }
            for (int i = 1; i <= 10; i++)             //先下
                if (human[i][1] == level && human[i][0] == 2) {
                    load--;
                    n--;
                    human[i][0] = 0;
                }
        }
        for(int i=turn;queue[i][0]<=time&&queue[i][1]!=0;i++,turn++)//从turn开始防止有人下了又上，循环防止多人同时按下按键
        {
            human[queue[i][1]][0]=1;
            if(queue[i][1]!=level)                //若按键的楼层和电梯所在楼层不一致
                requ(queue[i][1]);
        }
        if(human[level][0]==1){                         //后上
            if(load<4){
                load++;
                requ(human[level][1]);
                human[level][0]=2;
            }
            else{                        //要上电梯却满载荷，这是唯一一种无法当场解决的请求
                flag=1;                   //将在下次循环做有关处理，具体如循环开头flag部分
            }
        }
        if(request[level])                  //有操作则打印
            status();
        request[level]=flag;
        if(up==0&&down==0)                         //判断电梯接下来运动方向
            run=0;
        else if(up!=0&&down==0)
            run=1;
        else if(up==0&&down!=0)
            run=-1;
        else
            if(run==0){
                 for(int i=1;i<=10;i++) {
                     if (request[level + i]) {
                         run=1;
                         break;
                     }
                     else if (request[level - i]) {
                         run=-1;
                         break;
                     }
                 }
            }

    }
    return 0;
}