/*************************************************************************
> File Name: voxel_grid.cpp
> Author: 
> Mail: 
> Created Time: Di 29 Okt 2019 15:11:32 CET
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <cstring>
using namespace std;

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/visualization/pcl_visualizer.h>
using namespace pcl;


int main(int argc, char * argv[])
{
    // read the filename from the folder
    struct dirent *ptr;    
    DIR *dir;
    string PATH = ".";
    dir=opendir(PATH.c_str()); 
    vector<string> files;
    cout << "文件列表: "<< endl;
    while((ptr=readdir(dir))!=NULL)
    {

        //跳过'.'和'..'两个目录
        if(ptr->d_name[0] == '.')
        continue;
        //cout << ptr->d_name << endl;

        //cout << std::strlen(ptr->d_name) << endl;

        if(ptr->d_name[std::strlen(ptr->d_name)-1] != 'd')
        continue;
        files.push_back(ptr->d_name);
    }

    for (int i = 0; i < files.size(); ++i)
    {
        cout << files[i] << endl;
    }

    closedir(dir);


    pcl::visualization::PCLVisualizer viewer("Downsampling with VoxelGrid ");
    for(int i = 0; i < files.size();i++)
    //for(int i = 2; i < 2;i++)
    {
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>());
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGB>());

        // Fill in the cloud data
        pcl::PCDReader reader;
        reader.read (files[i], *cloud); // Remember to download the file first!

        std::cerr   << "PointCloud before filtering: " << cloud->width * cloud->height 
        << " data points (" << pcl::getFieldsList (*cloud) << ").\n";

        // Create the filtering object
        pcl::VoxelGrid<pcl::PointXYZRGB> sor;
        sor.setInputCloud (cloud);
        sor.setLeafSize (0.1f, 0.1f, 0.1f);
        sor.filter (*cloud_filtered);

        // print the result of filtering
        std::cerr   << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
        << " data points (" << pcl::getFieldsList (*cloud_filtered) << ").\n";

        // save the result in pcd file 
        // pcl::PCDWriter writer;
        // string name;
        // name = "downsampled_" + files[i];
        // writer.write (name, *cloud_filtered, Eigen::Vector4f::Zero (), Eigen::Quaternionf::Identity (), false);

        // visualization 

        //string origin_handler = "origin_" + files[i];
        string filtered_handler = "filtered_" + files[i];

        // define RGB 
        //pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> cloud_color_handler(cloud, 150, 150,150);
        //viewer.addPointCloud(cloud, cloud_color_handler, origin_handler);

        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> cloud_filtered_color_handler(cloud_filtered, (i*20)%255, (100+i*30)%255, (200+i*50)%255);
        viewer.addPointCloud(cloud_filtered, cloud_filtered_color_handler, filtered_handler);

        // set renderingproperties
        //viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, origin_handler);
        viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 7, filtered_handler);

        // visualization 
        // add frame
        viewer.addCoordinateSystem(1.0, "Frame", 0);
        // set background color
        viewer.setBackgroundColor(0.05, 0.05, 0.05, 0);

    }

    // display the visualiser until 'q' key is pressed
    while(!viewer.wasStopped())
    {
        viewer.spin();
    }
    return 0;
}
