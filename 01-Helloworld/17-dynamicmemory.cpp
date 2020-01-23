/*************************************************************************
	> File Name: 17-dynamicmemory.cpp
	> Author: 
	> Mail: 
	> Created Time: Mi 20 Nov 2019 16:44:00 CET
 ************************************************************************/

/*
 * C++ 程序中的内存分为两个部分：
 * 栈：在函数内部声明的所有变量都将占用栈内存。
 * 堆：这是程序中未使用的内存，在程序运行时可用于动态分配内存。
 * 
 * 在 C++中，您可以使用特殊的运算符为给定类型的变量在运行时分配堆内的内存，
 * 这会返回所分配的空间地址。这种运算符即 new 运算符。
 * 如果您不再需要动态分配的内存空间，可以使用 delete 运算符，
 * 删除之前由 new 运算符分配的内存。
 */ 


#include<iostream>
using namespace std;


int main()
{
    // use new to create a memory for the variable 
    double *pvalue = NULL;  // init a pointer with NULL 
    pvalue = new double;    // ask memory for the variable

    // store the value in this memory adress
    *pvalue = 29494.99029234;      
    cout << "Value of pvalue: " << *pvalue << endl;

    // 如果自由存储区已被用完，可能无法成功分配内存。
    // 所以建议检查 new 运算符是否返回 NULL 指针 
    double* pvalue1 = NULL;
    if(!(pvalue = new double))
    {
        cout << "Error: out of memory." << endl;
        exit(1);
    }

    // use delete to release the memory
    delete pvalue, pvalue1;  // release the memory

    // dynamic example ----------------------------------
    int m = 3;
    int n = 5;

    // one dimension array
    int *array1 = new int [m];

    delete [] array1;

    // two dimension array 
    int **array2;
    array2 = new int *[m];
    for(int i=0;i<m;i++)
    {
        array2[i] = new int [n];
    }
    
    // release 
    for(int i=0;i<m;i++)
    {
        delete [] array2[i]; 
    }

    delete [] array2;


    return 0;
}
