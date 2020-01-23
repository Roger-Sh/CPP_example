#include <iostream>
using namespace std;

//extern variable
//extern int a, b;
//extern int c;
//extern float f;

int main()
{
	//bool, char, int, float, double, void, wchar_t: short int, string
	int a, b;
	int c;
	float f;

	a = 10;
	b = 20;
	c = a + b;

	cout << c << endl;

	f = 70.0/3.0;
	cout << f << endl;


	//signed, unsigned, long, short
	short int i;				//有符号短整数
	short unsigned int j;		//无符号短整数
	

	j = 50000;
	i = j;

	cout << i << " " << j << endl;


	//c++ 11 nomore auto
	//auto, register, static, exern, mutable, thread_local
	//auto f = 3.14;						//double
	//auto s("hello");					//const char*
	//auto z = new auto(9)				//int*
	//auto x1 = 5, x2 = 5.0, x3 = 'r';	//必须是同类型的变量才可以用auto初始化

	

	
	//char*, char[], string
	const char* s1 = "abc";	//指针可以被修改，指向的字符串常量不可以修改 
	char s2[] = "abc";		//abc是在栈里面，数值可以被修改。但是s2作为数组指针不能指向其他地址空间 
	char* s3 = s2;			//p是和s1一样的指针，可以指向其他地址
	std::string s4 = "abc";

	cout << s1 << endl;
	cout << *s1 << endl;
	cout << &s1 << endl;
	cout << s2 << endl;
	cout << &s2 << endl;
	cout << *s2 << endl;
	cout << s2[0] << endl;
	cout << s3 << endl;
	cout << s4 << endl;


	//各种运算符
	//operation: +-*/ == != > < >= <= && || !	//操作运算符
	//= += -= *= /= %= <<= >>= &= ^= |=			//赋值运算符
	//sizeof()									//返回输入变量的大小
	//condition ? X:Y							//条件运算符
	//x.y x->y									//引用类，结构和共生体的成员	
	//int(2.20000)								//强制转换运算符
	
	//&  指针运算符 & 返回变量地址
	//*  指针运算符 * 指向一个变量的内容




    float ff;
    ff = 1122.345235634;

    cout << ff << endl;

    char aa[5];
    sprintf(aa, "%02.02f", ff);

    cout << aa << endl;








	return 0;
}
