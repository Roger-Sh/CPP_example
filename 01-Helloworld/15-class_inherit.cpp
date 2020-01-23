/*************************************************************************
> File Name: 15-class_inherit.cpp
> Author: 
> Mail: 
> Created Time: Di 22 Okt 2019 23:11:21 CEST
************************************************************************/

/*
继承inherit, 派生derived。继承允许我们依据另一个类来定义一个类，
这使得创建和维护一个应用程序变得更容易。
这样做，也达到了重用代码功能和提高执行效率的效果 
当一个类派生自基类，该基类可以被继承为 public、protected 或 private 几种类型

语法    class derived-class: access-specifier base-class
修饰符  access-specifier: public,protected, private
例子    class Rectangle: public Shape


多继承即一个子类可以有多个父类，它继承了多个父类的特性。
class <派生类名>:<继承方式1><基类名1>,<继承方式2><基类名2>,…
{
<派生类类体>

};

*/ 


#include<iostream>
using namespace std;

//基类
class Shape 
{
    public:
    void setWidth(int w)
    {
        width = w;      
    }
    void setHeight(int h)
    {
        height = h;      
    }
    protected:
    int width;
    int height;
};

// 基类 PaintCost
class PaintCost 
{
    public:
    int getCost(int area)
    {
        return area * 70;
    }
};

//派生类
/*
class Rectangle: public Shape
{
public:
int getArea()
{ 
return (width * height); 
    }
    };
    */ 

// 派生类
class Rectangle: public Shape, public PaintCost
{
    public:
    int getArea()
    { 
        return (width * height); 
    }
};

int main(void)
{
    Rectangle Rect;
    int area;	

    Rect.setWidth(5);
    Rect.setHeight(7);

    area = Rect.getArea();

    // 输出对象的面积
    cout << "Total area: " << Rect.getArea() << endl;

    // 输出总花费
    cout << "Total paint cost: $" << Rect.getCost(area) << endl;


    return 0;
}


