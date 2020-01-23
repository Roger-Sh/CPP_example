/*************************************************************************
	> File Name: 13-constructor.cpp
	> Author: 
	> Mail: 
	> Created Time: Di 22 Okt 2019 17:14:23 CEST
 ************************************************************************/

/*
类的构造函数是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。
构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。构造函数可用于为某些成员变量设置初始值。
*/

#include <iostream>
 
using namespace std;
 
//类 Line_1 
class Line_1
{
   public:
      void setLength( double len );
      double getLength( void );
      Line_1();  // 这是构造函数
 
   private:
      double length;
};
 
// 成员函数定义，包括构造函数，constructor一般名字和class一样，并且没有返回值，一般用来初始化类的成员变量，或者执行某些语句
Line_1::Line_1(void)
{
    cout << "Object is being created" << endl;
}
 
void Line_1::setLength( double len )
{
    length = len;
}
 
double Line_1::getLength( void )
{
    return length;
}


//类Line_2
class Line_2 
{
    public:
        void setLength( double len );
        double getLength( void );
        Line_2(double len);  // 这是构造函数
        ~Line_2();
 
    private:
        double length;
};

// 成员函数定义，包括构造函数,构造函数的输入变量在该类被实例化的时候输入
/*
Line_2::Line_2( double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}
*/

//使用初始化列表来初始化字段,和上面的效果一样，初始化列表用:来表示
Line_2::Line_2( double len):length(len)
{
    cout << "Object is being created, length = " << len << endl;
}


/*
假设有一个类 C，具有多个字段 X、Y、Z 等需要进行初始化，同理地，您可以使用上面的语法，只需要在不同的字段使用逗号进行分隔，如下所示：
C::C( double a, double b, double c): X(a), Y(b), Z(c)
{
  ....
}
*/

void Line_2::setLength( double len )
{
    length = len;
}

double Line_2::getLength( void )
{
    return length;
}

/*
类的析构函数是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行。
析构函数的名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀，
它不会返回任何值，也不能带有任何参数。析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。
*/ 
Line_2::~Line_2(void)
{
    cout << "Object is being deleted" << endl;
}

// 程序的主函数
int main( )
{
    Line_1 line_1;
 
    // 设置长度
    line_1.setLength(6.0); 
    cout << "Length of line : " << line_1.getLength() <<endl;
 

    Line_2 line_2(10.0);
 
    // 获取默认设置的长度
    cout << "Length of line : " << line_2.getLength() <<endl;
    // 再次设置长度
    line_2.setLength(6.0); 
    cout << "Length of line : " << line_2.getLength() <<endl;
    return 0;
}
