/*************************************************************************
	> File Name: 07-vector.cpp
	> Author: Weipu Shan 
	> Mail: weipu.shan@gmail.com
	> Created Time: Mi 16 Okt 2019 14:51:02 CEST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    //创建一个向量存储容器 int -------------------------------------------
    vector<int> object;
    for(int i =0; i < 10; i++)
    {
        object.push_back(i); //push_back()在数组最后添加数据 
        cout<<object[i]<<",";
    }
    
    cout << endl;
    
    for(int i=0;i<5;i++)
    {
        object.pop_back();//pop_back()去掉数组最后一个数据 
    }

    for(int i=0;i<object.size();i++) //size()  vector容器大小
    {
        cout<<object[i]<<",";
    }

    //清除容器内容---------------------------------------------------------
    object.clear(); 
    for(int i=0;i<object.size();i++)
    {
        cout<<object[i]<<endl;
    }

    //容器内排序-----------------------------------------------------------
    vector<int> object2;
    object2.push_back(1);
    object2.push_back(3);
    object2.push_back(0);
    
    cout<<*object2.begin()<<endl; //begin(), end() 输出的是指针
    cout<<*object2.end()<<endl;
    cout << endl;

    sort(object2.begin(),object2.end()); //sort() 从小到大排序
    cout<<"从小到大:"<<endl;
    for(int i=0;i<object2.size();i++)
    {
        cout<<object2[i]<<",";  
    } 

    cout<<endl;
 
    cout<<"从大到小:"<<endl;
    reverse(object2.begin(),object2.end());//从大到小 
    for(int i=0;i<object2.size();i++)
    {
        cout<<object2[i]<<",";
    }

    cout<<endl;

    
    //访问容器内容----------------------------------------------------------
    vector<int> object3;
    for(int i=0;i<10;i++)
    {
        object3.push_back(i);
    }

    //方法一，顺序访问
    cout<<"直接利用数组："; 
    for(int i=0;i<10;i++) 
    {
        cout<<object3[i]<<" ";
    }
    cout<<endl;

    //方法二，使用迭代器将容器中数据输出
    cout<<"利用迭代器：" ;
    //声明一个迭代器it，来访问vector容器，作用：遍历或者指向vector容器的元素
    vector<int>::iterator it;
    for(it=object3.begin();it!=object3.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;


    //二维数组定义方法
    //方法一
    int N=5,M=6;
    cout<<"二维数组"<<endl;
    vector< vector<int> > object4(N); //定义二维动态数组行数N
    cout<<"方法一"<<endl;
    for(int i=0; i < object4.size();i++)
    {
        object4[i].resize(M);       //定义二维数组每一行的列数为M
    }
    
    cout<<"数组大小："<<object4.size()<<" X "<<object4[0].size()<<endl;
    for(int i=0;i<object4.size();i++)
    {
        for(int j=0;j<object4[i].size();j++)
        {
            object4[i][j] = i*j;
            cout<<object4[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    //方法二
    cout<<"方法二"<<endl;
    vector<vector<int>> object5(N, vector<int>(M)); //二维数组五行六列
    for(int i=0; i<object5.size();i++)
    {
        for(int j=0;j<object5[i].size();j++)
        {
            object5[i][j] = i*j;
            cout<<object5[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;


    //vector 数学操作
    cout<<"vector math operate"<<endl;
    vector<int> object6;
    for (int i=0;i<3;i++)
    {
        object6.push_back(i);
    }
 
    for (int i=0;i<3;i++)
    {
        cout << object6[i] << endl;
    }

    return 0;
}


