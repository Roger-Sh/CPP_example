/*************************************************************************
	> File Name: 06-array.cpp
	> Author: 
	> Mail: 
	> Created Time: Mi 16 Okt 2019 14:27:39 CEST
 ************************************************************************/

#include<iostream>
using namespace std;

#include<iomanip>
using std::setw;        //setw() 格式化输出

#include<vector>


int main()
{
    //********************Array**************************
    int n[10];  //定义一个容量为10个元素的数组

    for(int i = 0; i < 10; i++)
    {
        n[i] = i + 100;
    }

    cout << "Element" << setw(13) << "Value" << endl;
    
    for(int j = 0; j < 10; j++)
    {
        cout << setw(7) << j << setw(13) << n[j] << endl;
    }

    //字符数组最后包含一个null****************************
    char a1[] = {'C', '+', '+'};          // 初始化，没有 null
    char a2[] = {'C', '+', '+', '\0'};    // 初始化，明确有 null
    char a3[] = "C++";                    // null 终止符自动添加
    //const char a4[6] = "runoob";          // 报错，没有 null 的位置


    //不固定大小的Vector **********************************
    
    //vector为变量类型，vec为变量名称，<>为vector中元素类型
    vector<int> vec;

    // 显示 vec 初始大小
    cout << "vector size = " << vec.size() << endl;

    // 向向量 vec 追加 5 个整数值
    for(int i = 0; i < 5; i++){
      vec.push_back(i);         //使用push_back()为vec添加元素
    }

    // 显示追加后 vec 的大小
    cout << "extended vector size = " << vec.size() << endl;
    












    return 0;
}
