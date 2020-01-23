/*************************************************************************
	> File Name: 19-json.cpp
	> Author: 
	> Mail: 
	> Created Time: Do 28 Nov 2019 10:57:48 CET
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;


#include <nlohmann/json.hpp>
using json = nlohmann::json;


int main()
{
    json j;

    j["array"].push_back(1);
    j["array"].push_back(2);
    j["array"].push_back(3);

    j["parameter"] = "abcde";

    cout << j["array"] << endl;

    std::vector<int> vec;

    vec.push_back(j["array"][0]);

    for(int i=0;i<3;i++)
    {
        cout << j["array"][i] << endl;
        
    }

    return 0;
}
