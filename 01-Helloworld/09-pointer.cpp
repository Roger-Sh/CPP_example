/*************************************************************************
	> File Name: 09-pointer.cpp
	> Author: 
	> Mail: 
	> Created Time: Fr 18 Okt 2019 16:56:08 CEST
 ************************************************************************/

#include<iostream>
using namespace std;

int main()
{
    int var1;
    char var2[10];

    cout << "var1 adress: " << &var1 << endl;
    cout << "var2 adress: " << &var2 << endl;

    int *ip;
    double *dp;
    float *fp;
    char *ch;

    int var = 20;   //实际变量声明
    int *ptr;       //指针变量声明

    ptr = &var;     //将实际变量的地址赋值给指针变量

    cout << "Value of var: " << var << endl;
    cout << "Adress of var, stored in ptr: " << ptr << endl;
    cout << "From adress of var, get the value of var: " << *ptr << endl;
    
    // & 取地址，*取值


/*
    引用很容易与指针混淆，它们之间有三个主要的不同：
    不存在空引用。引用必须连接到一块合法的内存。
    一旦引用被初始化为一个对象，就不能被指向到另一个对象。
    指针可以在任何时候指向到另一个对象。
    引用必须在创建时被初始化。指针可以在任何时间被初始化。
*/
    int i;
    double d;
    int& r = i;     //r为i的引用 

    double& s = d;  //初始化d的double型引用

    i = 5; 
    cout << "Value of i : " << i << endl;
    cout << "Value of i reference : " << r  << endl;
     
    d = 11.7;
    cout << "Value of d : " << d << endl;
    cout << "Value of d reference : " << s  << endl;

    return 0;
}
