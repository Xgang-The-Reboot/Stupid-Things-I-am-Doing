#include <stdio.h>
#include <stdlib.h>

int NumberExchange(int x,int y){
    int t;
    t=0;

    t=x;
    x=y;
    y=t;

    printf("%d,%d\n",x,y);
    return 0;
}

int TimeCalc(int h1,int m1,int h2,int m2){
    puts("接下来进入计算时间差的程序：");
    puts("请输入第一组时间：");
    scanf("%d %d",&h1,&m1);
    puts("请输入第二组时间：");
    scanf("%d %d",&h2,&m2);

    int M1=0,M2=0;
    M1=h1*60+m1;
    M2=h2*60+m2;
    int d=M2-M1;

    if(d<0)d=-d;//这种函数比较好的算法就是从一开始就对这一个整体做绝对值，而不是先拆分再分别处理。上来就拉了坨大的，我真他妈是个SuperBoy.
    int hd=d/60;
    int md=d%60;
    printf("两个时间相差%d小时%d分钟",hd,md);
    return 0;
}

void CashChange_Dusted(){
/*
 * 要想实现找零，首先我们需要
 * 知道用户给了多少钱
 * 知道商品价格是多少
 * 正确计算两者差值
 * 当然，发现差值是负数就应该告诉人家钱不够
 * 这套系统仅为现金支付设计
 * 我国现金面额从大到小有(包括硬币)：100.0,50.0,20.0,10.0,5.0,2.0(现在已经不再使用),1.0,0.5,0.1,0.01
 * 还得检查收银台有没有足够现金，如果现金存量不够的话还得切换到备用方案。为什么不一开始就做计算呢？
 * 最低支持0.01（一分钱），所以输出最多仅需支持两位小数
 *
 * 我有一个新的算法思路了，但是直接在石山上搭不是很好，新思路准备尽量用整形表示个变量
 * 因为我一要保证计算机运算正确，另一方面我要利用整形除法和取模特有的截断机制实现纸币分类
*/
    //先写最简单的算数模块？

    //首先是数据输入
    double have=0.0,price=0.0;
    puts("请输入商品价格：");
    scanf("%lf",&price);          //用AI检查出来这里并没有对输入内容做严格限定
    printf("您输入的价格是%0.2f\n",price);
    puts("客人的出价是：");
    scanf("%lf",&have);           //这里也是，查出来没有严格限制。但是先不管，之后可以修。
    //然后是数据计算
    float Change=have-price;
    if(Change<0){
        Change=-Change;
        printf("\a支付不足！客人还差：%0.2f元",Change);
        }
    else{
    printf("应该找零：%0.2f元\n",Change);
    }
}

void CashChangeV2(){               //本函数的编程受到AI辅助!!
/*理想情况下，这套系统最好是一点浮点数就别碰，因为浮点数只能保证一定位数有效数字的精度（float是6位，double是12位）
 * 一旦计算有问题，后续的截断就会把这个隐患直接变成炸弹：比如原来是23844.01就可能算成23843.99，完蛋！
 * 后面的人工展开简直就是屎，我了解到C语言是可以设计列表的，直接从列表集合里掏就行。
 */
    int price,have;
    float priceTemp,haveTemp,Change;
    puts("请输入商品价格：");
    scanf("%f",&priceTemp);
    puts("请输入客人出价：");
    scanf("%f",&haveTemp);
    if(haveTemp<priceTemp){
        Change=priceTemp-haveTemp;
        printf("支付不足，还差%0.2f\n",Change);
    }
    else{
        Change=haveTemp-priceTemp;
        printf("应该找零：%0.2f元\n",Change);
        price=priceTemp*100;
        have=haveTemp*100;
        //printf("测试输出：price=%d,have=%d\n",price,have);
        //测试完毕，正常截断
        int Ret0= have-price,Ret1,Ret2,Ret3,Ret4,Ret5,Ret6,Ret7,Ret8;
        //printf("测试输出：Ret0=%d\n",Ret0);
        //测试完毕，数值正常
        int Hundred= Ret0/10000;
        Ret1=Ret0%10000;
        int Fifty= Ret1/5000;
        Ret2=Ret1%5000;
        int Twenty=Ret2/2000;
        Ret3=Ret2%2000;
        int Ten=Ret3/1000;
        Ret4=Ret3%1000;
        int Five=Ret4/500;
        Ret5=Ret4%500;
        int One=Ret5/100;
        Ret6=Ret5%100;
        int five=Ret6/50;
        Ret7=Ret6%50;
        int one=Ret7/10;
        int _one=Ret8=Ret7%10;
        printf("对应：\n一百元：%d张\n五十元：%d张\n二十元：%d张\n十元：%d张\n五元：%d张\n一元：%d张/枚\n五角：%d张/枚\n一角：%d张/枚\n另有%d分钱\n",Hundred,Fifty,Twenty,Ten,Five,One,five,one,_one);
    }

}

void CashChangeV3(){               //本函数的编程受到AI辅助!!
/* 另外感谢我一位QQ好友的鼎力相助，他提出了很重要的意见：
 * “现在的游戏基本都只要整数部分了，细化角分厘对游戏性的影响很小”
 * 我设计这套系统主要是模拟现实收银，所以有细化的需求，他则提出
 * “最后输出显示的时候转 str （字符串），再添加 "." 即可”
 * 难点只在"输入怎么带小数进来"，这点确实，也是目前一直觉得很麻烦的问题
 */
    int price=0,have=0,change=0;
    puts("请输入商品价格：");

    puts("请输入客户出价：");

    if(have<price){
        change=price-have;
        puts("客户出价不足！还应支付：");
    }
    else{
        printf("应该找零：");
        int Cash[] = {10000,5000,2000,1000,500,100,50,10,1};
        int Ret[] = {0,1,2,3,4,5,6,7,8};
    }
}

void SwitchCase_Test(){
    int type=10;
    switch(type){
        case 1:
            puts("1");
            break;
        case 10:
            puts("10");
            break;
    }
}

int ScanAndMax(int x,int y,int z,int M){
    //这是个旧版比大小函数，新版的在下面
    scanf("%d %d %d",&x,&y,&z);
    if(x>y){
        if(x>z){
            M=x;
        }else{
            M=z;
        }
    }
    else if(y>z){
        M=y;
    }else{
        M=z;
    }
    return M;
}

long long int NumCnt(long long int Num){
//难绷int最多存十位数，要想更好用得上long long 超长整型
    int i;
    for(i=0;Num!=0;i++){
        Num=Num/10;
    }
    return i;
}

int ScanAndMaxPlus(int cnt){                //本函数的编程受到AI辅助！！
    int CycleCnt,n,max=0;
    puts("您要比较几个数字？");
    scanf("%d",&cnt);
    if(cnt<=0){
        puts("您输入的个数无效！");
        return 0;
    }
    puts("请输入要比较的数字，格式 'a b c d …… n' ：");
    scanf("%d",&max);

//for语句的优势是集合了“初始化、循环条件、更新行为”三者在一个语句里
//dpsk指出这种比大小的算法是“擂台式”算法，谁大谁上场，谁小谁被挤下去。
    for(CycleCnt=1;CycleCnt<cnt;CycleCnt++){
        scanf("%d",&n);
        if(n>max)max=n;
    }
    return max;


//主函数在这里！
}

int DelFl(double origin){
    int output;
    if(origin>=0){
        output = origin;
    }else{                                  //这一部分函数编写受AI辅助
        int tmp = origin;
        if(tmp>origin){
            tmp-- ;
            output = tmp;
        }
        else{
            output = origin;
        }
    }
    return output;
}

int DelFlV2(double input){
    int output = input; //直接给输入截断掉然后赋给输出，如果是正数的话，那这肯定就结束了
    if(output<0){       //如果不是正数的话，那就是向零截断
        output-- ;      //向下减一位
    }
    return output;
    //在C语言中也是有专门处理数学运算的库 <math.h>，
    //所以说这个函数拿来学习应该没啥问题，但是放到生产环境下就是多此一举
}

int main(){
    //int cnt=0;
    //printf("%d",ScanAndMaxPlus(cnt));
    //CashChange_Dusted();
    int intTest[]={-2,-1,0,1,2,3,4};
    float floatTest[]={-2.2,-1.45,-1,0,1,2.33,0.443};
    puts("======================取整函数测试现在开始======================");
    puts("===现在是整数测试===");
    for (int i1=0;i1<=6;i1++){
        printf("整数测试：%d\n",intTest[i1]);
        printf("%d\n",DelFlV2(intTest[i1]));
    }
    puts("===现在是浮点数测试===");
    for (int i2=0;i2<=6;i2++){
        printf("浮点数测试：%lf\n",floatTest[i2]);
        printf("%d\n",DelFlV2(floatTest[i2]));
    }
    return 0;
}

