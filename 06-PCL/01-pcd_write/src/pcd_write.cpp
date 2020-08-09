#include<iostream>
#include <pcl/io/pcd_io.h>      //pcl 输入输出库
#include <pcl/point_types.h>    //pcl 点类型库
using namespace std;

int main (int argc, char** argv)
{
    //定义点云变量cloud, 类型为pcl::PointCloud，其中点的类型为pcl::PointXYZ 
    pcl::PointCloud<pcl::PointXYZ> cloud;     

    // Fill in the cloud data
    cloud.width    = 5;         //点云的宽度   
    cloud.height   = 1;         //点云高度
    cloud.is_dense = false;     //是否稠密
    cloud.points.resize (cloud.width * cloud.height);   //定义点云的宽度高度，

    //对于每个点，填充随机的xyz数据
    for (size_t i = 0; i < cloud.points.size(); ++i)
    {
        cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);//保存cloud到一个pcd文件
    //cerr表示字符错误
    std::cerr << "Saved " << cloud.points.size () << " data points to test_pcd.pcd." << std::endl;

    //输出每个点xyz的数据到屏幕
    for (size_t i = 0; i < cloud.points.size (); ++i)
        std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;

    return (0);
}
