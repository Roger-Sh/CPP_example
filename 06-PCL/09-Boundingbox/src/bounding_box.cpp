/*************************************************************************
	> File Name: bounding_box.cpp
	> Author: 
	> Mail: 
	> Created Time: Mi 04 Dez 2019 15:28:51 CET
 ************************************************************************/

// std 
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <cstring>
#include <bits/stdc++.h> 

// pcl 
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>

// eigen 
#include <Eigen/Geometry> 


Eigen::Vector3f getBoundingBox( pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,  
                                Eigen::Vector3f center,
                                Eigen::Vector3f model)
{
    // length of bounding_box: x y z 
    Eigen::Vector3f bounding_box;
    
    // center_point_vec, vector from center to every point 
    std::vector< std::vector<float> > center_point_vec(cloud->points.size(), std::vector<float>(3));
    for(size_t i=0;i<cloud->points.size();i++)
    {
        center_point_vec[i][0] = cloud->points[i].x - center[0]; 
        center_point_vec[i][1] = cloud->points[i].y - center[1]; 
        center_point_vec[i][2] = cloud->points[i].z - center[2]; 
    }

    // length of x -------------------------------------------------------------------------------------------------------------
    // project from center_point_vec[i] on normal vector 
    std::vector<float> project_x;
    for(size_t i=0;i<cloud->points.size();i++)
    {
        // Formel: project_length = a*b/|b|
        float scalar_product_x = center_point_vec[i][0]*model[0]+center_point_vec[i][1]*model[1]+center_point_vec[i][2]*model[2];
        float normierung_x = sqrt(model[0]*model[0]+model[1]*model[1]+model[2]*model[2]);
        float project_x_i = std::fabs(scalar_product_x/normierung_x);
        project_x.push_back(project_x_i);
    }
    float max_x = *max_element(project_x.begin(), project_x.end());
    bounding_box[0] = max_x;


    // length of y ------------------------------------------------------------------------------------------------------------- 
    Eigen::Vector3f vector_y;
    Eigen::Vector3f vector_z; 

    vector_z[0] = 0.0;
    vector_z[1] = 0.0;
    vector_z[2] = 1.0;

    vector_y[0] = vector_z[1]*model[2] - vector_z[2]*model[1]; 
    vector_y[1] = vector_z[2]*model[0] - vector_z[0]*model[2]; 
    vector_y[2] = vector_z[0]*model[1] - vector_z[1]*model[0];

    std::vector<float> project_y;
    for(size_t i=0;i<cloud->points.size();i++)
    {
        // Formel: project_length = a*b/|b|
        float scalar_product_y = center_point_vec[i][0]*vector_y[0]+center_point_vec[i][1]*vector_y[1]+center_point_vec[i][2]*vector_y[2];
        float norm_y = sqrt(vector_y[0]*vector_y[0]+vector_y[1]*vector_y[1]+vector_y[2]*vector_y[2]);
        float project_y_i = std::fabs(scalar_product_y/norm_y);
        project_y.push_back(project_y_i);
    }
    float max_y = *max_element(project_y.begin(), project_y.end());
    bounding_box[1] = max_y;



    // length of z ------------------------------------------------------------------------------------------------------------- 
    std::vector<float> project_z;
    for(size_t i=0;i<cloud->points.size();i++)
    {
        float project_z_i = std::fabs(cloud->points[i].z - center[2]);
        project_z.push_back(project_z_i);
    }
    float max_z = *max_element(project_z.begin(), project_z.end()); 
    bounding_box[2] = max_z;

    return bounding_box;
}

int main(int argc, char * argv[])
{
    // read the filename from the folder
    struct dirent *ptr;    
    DIR *dir;
    std::string PATH = ".";
    dir=opendir(PATH.c_str()); 
    std::vector<std::string> files;
    cout << "文件列表: "<< endl;
    while((ptr=readdir(dir))!=NULL)
    {
        // skip '.' and '..'
        if(ptr->d_name[0] == '.')
        continue;
        //cout << ptr->d_name << endl;

        //cout << std::strlen(ptr->d_name) << endl;

        if(ptr->d_name[std::strlen(ptr->d_name)-1] != 'd')
        continue;
        files.push_back(ptr->d_name);
    }

	// print file name 
    for (int i = 0; i < files.size(); ++i)
    {
        cout << files[i] << endl;
    }

    closedir(dir);

    // Pointcloud fill in  
    pcl::PCDReader reader;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>());
    reader.read(files[0], *cloud);



    // Center  
    Eigen::Vector3f center;
    center[0] = 7.498;
    center[1] = 0.905;
    center[2] = 1.812;

    // Normal vector, Vector X from plane 
    Eigen::Vector3f model;
    model[0] = 0.047;
    model[1] = -0.999;
    model[2] = -0.007;

    // Vector Y from plane 
    Eigen::Vector3f vector_y;
    Eigen::Vector3f vector_z; 
    vector_z[0] = 0.0;
    vector_z[1] = 0.0;
    vector_z[2] = 1.0;
    vector_y[0] = vector_z[1]*model[2] - vector_z[2]*model[1]; 
    vector_y[1] = vector_z[2]*model[0] - vector_z[0]*model[2]; 
    vector_y[2] = vector_z[0]*model[1] - vector_z[1]*model[0]; 

    // Vector Z from plane, not 100% vertical, according to normal vector 
    vector_z[0] = model[1]*vector_y[2] - model[2]*vector_y[1]; 
    vector_z[1] = model[2]*vector_y[0] - model[0]*vector_y[2]; 
    vector_z[2] = model[0]*vector_y[1] - model[1]*vector_y[0]; 

    // Rotationsmatrix, Basis Frame -> Plane Frame
    Eigen::Matrix3f rot;
    rot(0,0) = model[0];
    rot(1,0) = model[1];
    rot(2,0) = model[2];
    rot(0,1) = vector_y[0];
    rot(1,1) = vector_y[1];
    rot(2,1) = vector_y[2];
    rot(0,2) = vector_z[0];
    rot(1,2) = vector_z[1];
    rot(2,2) = vector_z[2];

    // Quaternion, w + xi + yj + zk  
    Eigen::Quaternionf quat1 = Eigen::Quaternionf(rot);

    // Eigen::Quaternionf::coeffs(), return x, y, z, w
    Eigen::Vector4f quat1_coeffts = quat1.coeffs();   
    cout << "Rotationsmatrix: " << endl << rot << endl;
    cout << "Quaternion1: " << quat1_coeffts << endl; 
    Eigen::Matrix3f rot_from_quat = quat1.toRotationMatrix();
    cout << "RotationMatrix from Quaternion: " << endl << rot_from_quat << endl;












    // visualization 
    pcl::visualization::PCLVisualizer viewer("Boundingbox");
    // cloud_handler 
    std::string cloud_handler = files[0];
    // cloud_color_handler 
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> cloud_color_handler(cloud, 250, 10, 10);
    // addPointCloud() 
    viewer.addPointCloud(cloud, cloud_color_handler, cloud_handler);
    // setPointCloudRenderingProperties() 
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 7, cloud_handler);
    // add frame
    viewer.addCoordinateSystem(1.0, "Frame", 0);
    // set background color 
    viewer.setBackgroundColor(0.05, 0.0, 0.05, 0);

    // start and end point of arrow 
    pcl::PointXYZRGB A1,A2,A3,B;
	A1.x = center[0]+model[0]; A1.y = center[1]+model[1]; A1.z = center[2]+model[2];      // end point, centroid + normal vector  
	A2.x = center[0]+vector_y[0]; A2.y = center[1]+vector_y[1]; A2.z = center[2]+vector_y[2];      // end point, centroid + normal vector  
	A3.x = center[0]+vector_z[0]; A3.y = center[1]+vector_z[1]; A3.z = center[2]+vector_z[2];      // end point, centroid + normal vector  
	
    B.x = center[0]; B.y = center[1]; B.z = center[2];      // start point, centroid 

    // arrow
    viewer.addArrow<pcl::PointXYZRGB>(A1, B, 255, 10, 10, false, "arrowx", 0);
    viewer.addArrow<pcl::PointXYZRGB>(A2, B, 255, 10, 10, false, "arrowy", 0);
    viewer.addArrow<pcl::PointXYZRGB>(A3, B, 255, 10, 10, false, "arrowz", 0);

    // getBoundingBox() 
    Eigen::Vector3f bounding_box;
    bounding_box = getBoundingBox(cloud, center, model);
    cout <<"Bounding-Box size: " << bounding_box << endl;

    // bounding_box corner 
    std::vector< std::vector<float> > corner(8, std::vector<float>(3));
    geometry_msgs::Point p1, p2, p3, p4, p5, p6, p7, p8;
    P0.x = center[0] + model[0]*bounding_box[0] - vector_y[0]*bounding_box[1] + vector_z[0]*bounding_box[2];
    P1.x = center[0] + model[0]*bounding_box[0] + vector_y[0]*bounding_box[1] + vector_z[0]*bounding_box[2];
    P2.x = center[0] + model[0]*bounding_box[0] - vector_y[0]*bounding_box[1] - vector_z[0]*bounding_box[2];
    P3.x = center[0] + model[0]*bounding_box[0] + vector_y[0]*bounding_box[1] - vector_z[0]*bounding_box[2];
    P4.x = center[0] - model[0]*bounding_box[0] - vector_y[0]*bounding_box[1] + vector_z[0]*bounding_box[2];
    P5.x = center[0] - model[0]*bounding_box[0] + vector_y[0]*bounding_box[1] + vector_z[0]*bounding_box[2];
    P6.x = center[0] - model[0]*bounding_box[0] - vector_y[0]*bounding_box[1] - vector_z[0]*bounding_box[2];
    P7.x = center[0] - model[0]*bounding_box[0] + vector_y[0]*bounding_box[1] - vector_z[0]*bounding_box[2];
   
    P0.y = center[1] + model[1]*bounding_box[0] - vector_y[1]*bounding_box[1] + vector_z[1]*bounding_box[2];
    P1.y = center[1] + model[1]*bounding_box[0] + vector_y[1]*bounding_box[1] + vector_z[1]*bounding_box[2];
    P2.y = center[1] + model[1]*bounding_box[0] - vector_y[1]*bounding_box[1] - vector_z[1]*bounding_box[2];
    P3.y = center[1] + model[1]*bounding_box[0] + vector_y[1]*bounding_box[1] - vector_z[1]*bounding_box[2];
    P4.y = center[1] - model[1]*bounding_box[0] - vector_y[1]*bounding_box[1] + vector_z[1]*bounding_box[2];
    P5.y = center[1] - model[1]*bounding_box[0] + vector_y[1]*bounding_box[1] + vector_z[1]*bounding_box[2];
    P6.y = center[1] - model[1]*bounding_box[0] - vector_y[1]*bounding_box[1] - vector_z[1]*bounding_box[2];
    P7.y = center[1] - model[1]*bounding_box[0] + vector_y[1]*bounding_box[1] - vector_z[1]*bounding_box[2];

    P0.z = center[2] + model[2]*bounding_box[0] - vector_y[2]*bounding_box[1] + vector_z[2]*bounding_box[2];
    P1.z = center[2] + model[2]*bounding_box[0] + vector_y[2]*bounding_box[1] + vector_z[2]*bounding_box[2];
    P2.z = center[2] + model[2]*bounding_box[0] - vector_y[2]*bounding_box[1] - vector_z[2]*bounding_box[2];
    P3.z = center[2] + model[2]*bounding_box[0] + vector_y[2]*bounding_box[1] - vector_z[2]*bounding_box[2];
    P4.z = center[2] - model[2]*bounding_box[0] - vector_y[2]*bounding_box[1] + vector_z[2]*bounding_box[2];
    P5.z = center[2] - model[2]*bounding_box[0] + vector_y[2]*bounding_box[1] + vector_z[2]*bounding_box[2];
    P6.z = center[2] - model[2]*bounding_box[0] - vector_y[2]*bounding_box[1] - vector_z[2]*bounding_box[2];
    P7.z = center[2] - model[2]*bounding_box[0] + vector_y[2]*bounding_box[1] - vector_z[2]*bounding_box[2];

    // bounding_box line 
    viewer.addLine(P0, P1, 255, 0, 0, "line0", 0);  
    viewer.addLine(P1, P5, 255, 0, 0, "line1", 0);  
    viewer.addLine(P5, P4, 255, 0, 0, "line2", 0);  
    viewer.addLine(P4, P0, 255, 0, 0, "line3", 0);  
    viewer.addLine(P0, P2, 255, 0, 0, "line4", 0);  
    viewer.addLine(P1, P3, 255, 0, 0, "line5", 0);  
    viewer.addLine(P4, P6, 255, 0, 0, "line6", 0);  
    viewer.addLine(P5, P7, 255, 0, 0, "line7", 0);  
    viewer.addLine(P2, P3, 255, 0, 0, "line8", 0);  
    viewer.addLine(P3, P7, 255, 0, 0, "line9", 0);  
    viewer.addLine(P7, P6, 255, 0, 0, "line10", 0);  
    viewer.addLine(P6, P2, 255, 0, 0, "line11", 0);  
    // viewer.spin()
    while(!viewer.wasStopped())
    {
        viewer.spin();
    }

    return 0;
}
