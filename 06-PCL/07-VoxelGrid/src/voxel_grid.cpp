/*************************************************************************
> File Name: voxel_grid.cpp
> Author: 
> Mail: 
> Created Time: Di 29 Okt 2019 15:11:32 CET
************************************************************************/

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/visualization/pcl_visualizer.h>

int main (int argc, char** argv)
{
    pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
    pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());

    // Fill in the cloud data
    pcl::PCDReader reader;
    // Replace the path below with the path where you saved your file
    // reader.read ("table_scene_lms400.pcd", *cloud); // Remember to download the file first!
    reader.read ("test_pcd.pcd", *cloud); // Remember to download the file first!

    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height 
    << " data points (" << pcl::getFieldsList (*cloud) << ").\n";

    // Create the filtering object
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (0.2f, 0.2f, 0.2f);
    sor.filter (*cloud_filtered);

    // print the result of filtering
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
    << " data points (" << pcl::getFieldsList (*cloud_filtered) << ").\n";

    // save the result in pcd file 
    pcl::PCDWriter writer;
    writer.write ("test_pcd_downsampled.pcd", *cloud_filtered, 
                  Eigen::Vector4f::Zero (), Eigen::Quaternionf::Identity (), false);


    // transform the PCLPointCloud2 to PointCloud 
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_tf (new pcl::PointCloud<pcl::PointXYZ> ()); 
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_tf (new pcl::PointCloud<pcl::PointXYZ> ());

    pcl::fromPCLPointCloud2 (*cloud, *cloud_tf);
    pcl::fromPCLPointCloud2 (*cloud_filtered, *cloud_filtered_tf);


    // visualization 
    printf("Point cloud colors: white  - original point cloud\n"
           "                    red    - filtered point cloud\n");
    pcl::visualization::PCLVisualizer viewer("Downsampling with VoxelGrid ");

    // define RGB 
    // pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_tf_color_handler(cloud_tf, 255, 255, 255);
    // viewer.addPointCloud(cloud_tf, cloud_tf_color_handler, "original_cloud");
    
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_filtered_tf_color_handler(cloud_filtered_tf, 250 - i * 10, 20, 20);
    viewer.addPointCloud(cloud_filtered_tf, cloud_filtered_tf_color_handler, "filtered_cloud");

    // add frame
    viewer.addCoordinateSystem(1.0, "Frame", 0);
    
    // set background color
    viewer.setBackgroundColor(0.05, 0.05, 0.05, 0);

    // set renderingproperties
    // viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "filtered_cloud");

    // display the visualiser until 'q' key is pressed
    while(!viewer.wasStopped())
    {
        viewer.spinOnce();
    }
    
    return (0);
}
