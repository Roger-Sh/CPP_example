/*************************************************************************
	> File Name: stringToNumber.cpp
	> Author: 
	> Mail: 
	> Created Time: Fr 06 Dez 2019 13:42:24 CET
 ************************************************************************/

#include<iostream>
using namespace std;

#include <sstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s="3.24";
    double i=0.0;
    sscanf(s.c_str(),"%lf",&i);
    cout<<i<<endl;
    i=0.0;
    istringstream ss(s);
    
    ss>>i;
    cout<<i<<endl;

}
