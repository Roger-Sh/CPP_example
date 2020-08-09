/*************************************************************************
	> File Name: 01-eigen-example.cpp
	> Author: 
	> Mail: 
	> Created Time: Di 14 Jan 2020 13:40:28 CET
 ************************************************************************/

#include <iostream>
#include <Eigen/Dense>


int main()
{
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    Eigen::MatrixXd m1 = Eigen::MatrixXd::Random(3,3);
    m1 = (m1 + Eigen::MatrixXd::Constant(3,3,1.2)) * 50;
    std::cout << "m1 =" << std::endl << m1 << std::endl;
    Eigen::VectorXd v1(3);
    v1 << 1, 2, 3;
    std::cout << "m1 * v1 =" << std::endl << m1 * v1 << std::endl;


    Eigen::Matrix3f m2;
    m2 <<   1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    std::cout << m2 << std::endl;


    std::cout << "A fixed-size array: " << std::endl;
    Eigen::Array33f a1 = Eigen::Array33f::Zero();
    std::cout << a1 << std::endl;

    std::cout << "A one-dimensional dynamic-size array: " << std::endl;
    Eigen::ArrayXf a2 = Eigen::ArrayXf::Zero(3);
    std::cout << a2 << std::endl;
    std::cout << "A two-dimensional dynamic-size array: " << std::endl;
    Eigen::ArrayXXf a3 = Eigen::ArrayXXf::Zero(3, 4);
    std::cout << a3 << std::endl;

//    Eigen::MatrixX m3 = Eigen::Matrix::Zero(int, 480, 640);
//    std::cout << m3 << std::endl;
}
