#include <stdio.h>//暴力模拟扫描
#include <stdbool.h>
bool print;//打印判断
int run=1,human[11][2],level,time,load=0,flag;//human[i][1]储存第i层客户目的地,human[i][0]储存乘客状态
int c_in1,c_in2;                                //乘客状态：0为下电梯或不存在，1为等待电梯，2为在电梯上
bool empty()//判断是否完成所有任务
{
    for(int i=1;i<=10;i++)
        if(human[i][0]!=0)
            return 0;
    return 1;
}
void out_status()
{
    printf("%d %d %d\n",level,time,load);
}
int main()
{
    printf("Please enter passengers' information (one person per line), and enter a '0 0' at the end.\n");
    for(int i=0;i<=1;i++)
        for(int j=1;j<=10;j++)
            human[j][i]=0;
    while(1)
    {
        scanf("%d %d",&c_in1,&c_in2);
        if(c_in1==0)
            break;
        human[c_in1][0]=1;
        human[c_in1][1]=c_in2;
    }
    printf("1,0,0\n");//打印初始状态
    time=-1;//后面循环中每层判定都会time++，但出发的那层判定不应当计入总时间
    level=0;//原因同上
    while(empty()==0)//
    {
        print=0;//初始化打印判断
        time++;
        level+=run;//run为1或-1，控制上下行
        for(int i=1;i<=10;i++)//先下
        {
            if(human[i][1]==level&&human[i][0]==2)
            {
                print=1;
                load--;
                human[i][1]=0;
                human[i][0]=0;
            }
        }
        if(human[level][0]==1&&load<4)//后上
        {
            print=1;
            human[level][0]=2;
            load++;
        }
        switch (level){
            case 10:
                run=-1;
                break;
            case 1:
                run=1;
                break;
            default:
                flag=0;
                for(int i=level+run;i>=1&&i<=10;i+=run)//判断运行方向上是否有等待者
                    if(human[i][0]!=0)
                        flag=1;
                for(int i=1;i<=10;i++)
                    if((human[i][1]-level)*run>0)//判断运行方向上是否有目的地
                        flag=1;
                if(flag==0)
                    run*=-1;
                break;
        }
        if(print!=0)
            out_status();
    }
    return 0;
}