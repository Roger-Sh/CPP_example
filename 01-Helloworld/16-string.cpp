/*************************************************************************
> File Name: 16-string.cpp
> Author: 
> Mail: 
> Created Time: Mi 30 Okt 2019 15:07:53 CET
************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main ()
{
    string str1 = "Hello";
    string str2 = "World";
    string str3;
    int  len ;

    // 复制 str1 到 str3
    str3 = str1;
    cout << "str3 : " << str3 << endl;

    // 连接 str1 和 str2
    str3 = str1 + str2;
    cout << "str1 + str2 : " << str3 << endl;

    // 连接后，str3 的总长度
    len = str3.size();
    cout << "str3.size() :  " << len << endl;

    string str4;
    string str5;
    string str6;
    for(int i = 0; i < 5; i++)
    {
        str4 = "现在i到了数字：";
        str5 = to_string(i);
        str6 = str4 + str5;
        cout << str6 << endl;
    }
    
    return 0;
}
