#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    struct{
        char *name;   //姓名
        int num;   //学号
        int age;      //年龄
        char group;   //所在小组
        float score;  //成绩
    } stu1,stu2;
#if 1   
    stu1.name ="Tom";
    stu1.num  =12;
    stu1.age  =18;
    stu1.group='A';
    stu1.score=136.5;
    stu2.score=136.5;
#endif    
    printf("%s的学号是%d,年龄是%d在%c组今年的成绩是%.1f\n",stu1.name,stu1.num,stu1.age,stu1.group,stu1.score);
    printf("成绩是%.1f\n",stu2.score);
    return 0;
}
