/*************************************************************************
	> File Name: 05-math.cpp
	> Author: weipu.shan  
	> Mail: weipu.shan@gmail.com        
	> Created Time: Mi 16 Okt 2019 13:55:18 CEST
 ************************************************************************/

#include<iostream>
#include<cmath>

#include<ctime>
#include<cstdlib>

using namespace std;
int main()
{
    short s = 10;
    int i = -1000;
    long l = 100000;
    float f = 230.47;
    double d = 200.374;

    cout << "sin(d): " << sin(d) << endl;
    cout << "abs(i): " << abs(i) << endl;
    cout << "floor(d): " << floor(d) << endl;
    cout << "sqrt(f): " << sqrt(f) << endl;
    cout << "pow(d,2): " << pow(d,2) << endl;

    int j;
    
    srand((unsigned)time(NULL));

    //10 random numbers
    for(i=0;i<10;i++)
    {
        j = rand();
        cout << "random number: " << j << endl;
    }

    //double a = 2.0**2;
    //cout << a << endl;


    float x = 635;
    int px_x = x/6.25+1;
    cout << px_x << endl;
    float y = -3.5;
    int px_y = y/1-1;
    cout << px_y << endl;
    
    
    
    
    
    return 0;
}
