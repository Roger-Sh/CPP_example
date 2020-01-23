#include <iostream>

using namespace std;		//命名空间std封装的是标准程序库的名称


int max(int num1, int num2)
{
	int result;

	if(num1 > num2)
		result = num1;
	else
		result = num2;

	return result;
};

int sum(int a, int b)
{
	int result;

	result = a + b;

	return result;
}

//function, 参数的传递有： 传值调用，指针调用， 引用调用
//值传递
void change1(int n)
{
    cout << "值传递--函数操作地址：" << &n << endl;//显示的是拷贝的地址，而不是源地址
    n++;
}
//引用传递
void change2(int &n)
{
    cout << "引用传递--函数操作地址：" << &n << endl;
    n++;
}

//指针传递
void change3(int *n)
{
    cout << "指针传递--函数操作地址: " << n << endl;
    *n = *n + 1;
}

int main()
{
	int a = 100;
	int b = 200;
	int ret1, ret2;

	ret1 = max(a, b);

	cout << "Max value is: " << ret1 << endl;

	ret2 = sum(a, b);
	cout << "Sum value is: " << ret2 << endl;


    int n = 10;
    cout << "实参的地址" << &n << endl;
    change1(n);
    cout << "after change1(), n = " << n << endl;
    change2(n);
    cout << "after change2(), n = " << n << endl;
    change3(&n);
    cout << "after change3(), n = " << n << endl;

	return 0;
}
