/*************************************************************************
	> File Name: 10-union.cpp
	> Author: 
	> Mail: 
	> Created Time: Di 22 Okt 2019 15:51:58 CEST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
 
union Data
{
   int i;
   float f;
   char  str[20];
};
 
int main( )
{
    union Data data;        
 
    data.i = 10;
    data.f = 220.5;
    strcpy( data.str, "C Programming");
 
    printf( "data.i : %d\n", data.i);
    printf( "data.f : %f\n", data.f);
    printf( "data.str : %s\n", data.str);
    //共用体的 i 和 f 成员的值有损坏，因为最后赋给变量的值占用了内存位置

    //下面是正确的使用范例
    data.i = 10;
    printf( "data.i : %d\n", data.i);
   
    data.f = 220.5;
    printf( "data.f : %f\n", data.f);
   
    strcpy( data.str, "C Programming");
    printf( "data.str : %s\n", data.str);
 
    return 0;
}
