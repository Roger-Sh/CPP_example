/*************************************************************************
	> File Name: Circle.cpp
	> Author: 
	> Mail: 
	> Created Time: Mi 12 Feb 2020 16:17:15 CET
 ************************************************************************/
#include "Circle.h"

// constructor without input 
Circle::Circle()
{
    this->r=5.0;
}

// constructor with input 
Circle::Circle(double R)
{
    this->r=R;
}

double Circle::Area()
{
    return 3.14*r*r;
}
