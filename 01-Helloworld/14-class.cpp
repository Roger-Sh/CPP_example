/*************************************************************************
	> File Name: 14-class.cpp
	> Author: 
	> Mail: 
	> Created Time: Di 22 Okt 2019 22:55:20 CEST
 ************************************************************************/

/*
类用于指定对象的形式，它包含了数据表示法和用于处理数据的方法。
类中的数据和方法称为类的成员。函数在一个类中被称为类的成员。
 
定义一个类，本质上是定义一个数据类型的蓝图。这实际上并没有定义任何数据，
但它定义了类的名称意味着什么，也就是说，它定义了类的对象包括了什么，
以及可以在这个对象上执行哪些操作。
*/ 


#include<iostream>
using namespace std;

class Box
{
    public:                 //公共成员在类的外部是可访问的
        double length;      // 盒子的长度
        double breadth;     // 盒子的宽度
        double height;      // 盒子的高度
    //私有的成员和受保护的成员不能使用直接成员访问运算符 (.) 来直接访问
};

int main()
{
    Box Box1;
    Box Box2;

    double volume = 0.0;

    Box1.height = 5.0; 
    Box1.length = 6.0; 
    Box1.breadth = 7.0;

    Box2.height = 10.0;
    Box2.length = 12.0;
    Box2.breadth = 13.0;

    volume = Box1.height * Box1.length * Box1.breadth;
    cout << "Box1 的体积：" << volume <<endl;

    volume = Box2.height * Box2.length * Box2.breadth;
    cout << "Box2 的体积：" << volume <<endl;
    
    
    return 0;
}
