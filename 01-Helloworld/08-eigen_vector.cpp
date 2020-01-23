/*************************************************************************
	> File Name: 08-eigen_vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Mi 16 Okt 2019 16:18:54 CEST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <eigen3/Eigen/Dense> 
#include <eigen3/Eigen/StdVector>
 
using namespace std;
struct mystruct             //定义一个数据结构
{
	Eigen::Vector2d v2;
	Eigen::Matrix2f m2;
};
 
int main()
{
    //vector容器内如果包含自己定义的数据结构,并且大小不定，需要使用eigen自己定义的内存分配器，即aligned_allocator 
    vector<mystruct, Eigen::aligned_allocator<mystruct>> a;
	mystruct b;

    for (int i = 0; i < 4; i++)
	{
		//初始化一个数据结构b
        b.v2 = Eigen::Vector2d(1, 1);
		b.m2 = Eigen::Matrix2f::Identity();
		
        //将数据结构b保存到向量a中
        a.push_back(b);


	}

    cout<<b.v2<<endl;
    cout<<b.m2<<endl;

	return 0;
}


