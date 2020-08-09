/*************************************************************************
	> File Name: cxx_test.cpp
	> Author: Weipu Shan
	> Mail: weipu.shan@gmail.com
	> Created Time: Do 21 Nov 2019 16:51:29 CET
 ************************************************************************/

#include <libcouchbase/couchbase++.h>
#include <libcouchbase/couchbase++/views.h>
#include <libcouchbase/couchbase++/query.h>
#include <libcouchbase/couchbase++/endure.h>
#include <libcouchbase/couchbase++/logging.h>
using namespace Couchbase;

#include <cassert>      //library for error
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h> // read file 
#include <cstring>
using namespace std;

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
using namespace pcl;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

static void storeWall(Couchbase::Client *h_ptr)
{

    // read the filename from the folder
    struct dirent *ptr;
    DIR *dir;
    string PATH = ".";
    dir = opendir(PATH.c_str());
    vector<string> files;
    cout << "File list: " << endl;
    while((ptr=readdir(dir))!=NULL)
    {
        // skip ./ and ../
        if(ptr->d_name[0] == '.')
            continue;
        // skip none-pcd file 
        if( ptr->d_name[std::strlen(ptr->d_name)-3] != 'p' and
            ptr->d_name[std::strlen(ptr->d_name)-2] != 'c' and
            ptr->d_name[std::strlen(ptr->d_name)-1] != 'd' )
            continue;
        files.push_back(ptr->d_name);
    }
    for(unsigned i=0; i < files.size(); i++)
    {
        cout << files[i] << endl;
    }
    closedir(dir);

    // loop for saving the pcd file to json 
    for(unsigned i = 0; i < files.size();i++)
    {
        
        // Fill in the cloud data
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>());
        pcl::PCDReader reader;
        reader.read (files[i], *cloud);

        // Init a 2D Vector , n=cloud->points.size(), m = 3
        int N = (int)cloud->points.size();
        int M = 3;
        vector<vector<float>> point_vec(N, vector<float>(M));
        
        // save points to vector 
        for(int n=0;n<N;n++)
        {
            point_vec[n][0] = cloud->points[n].x;
            point_vec[n][1] = cloud->points[n].y;
            point_vec[n][2] = cloud->points[n].z;
        }

        // vector -> JSON -> string 
        json wall_planes;
        wall_planes["Points"] = point_vec;   
        string value_string = wall_planes.dump(); 
        // key
        char key[9];
        sprintf(key, "wall_%03d", (int)i);
        // item upsert 
        auto sres = h_ptr->upsert(key, value_string);
        // store status, cas
        cout << "Got status for store. Cas = " << std::hex << sres.cas() << endl;
    
    
    }
}

// storeDoc()
static void storeDoc(Couchbase::Client *h_ptr)
{
    // key and value
    string key("cxx-test");
    //string value_string("{ \"v\": 100.1, \"list\": [1,2,3,4,5,6,7], \"talk\": \"About Foo.\" }");


    // vector 
    vector<int> vec;

    for(int i = 0; i < 5; i++)
    {
        vec.push_back(i);
    }
    cout << "vector size = " << vec.size() << endl;

    // json 
    json value_json = {
        {"first_name", "weipu"},
        {"last_name", "shan"},
        {"gender", "male"},
        {"age", 26},
        {"hobby", {"movie", "fotograph", "game"}},
        {"object",  {
                        {"currency", "USD"},
                        {"value", 42.99}
                    }
        },
        {"Array", vec}
    };

    cout << value_json["first_name"] << endl;

    string value_string = value_json.dump();

    // item upsert 
    auto sres = h_ptr->upsert(key, value_string);
    
    // store status, cas
    cout << "Got status for store. Cas = " << std::hex << sres.cas() << endl;
}

// getDoc()
static void getDoc(Couchbase::Client *h_ptr)
{
    // key 
    string key("cxx-test");
    
    // item get 
    auto gres = h_ptr->get(key);
    cout << "Got value: " << gres.value() << endl;
    
    // json::parse(), convert value_string to value_json  
    std::string value_string = gres.value();
    json value_json = json::parse(value_string);
    cout << value_json["first_name"] << endl;
}

int main(int argc, const char **argv)
{
    // connect options-----------------------------------------
    string connstr("couchbase://localhost/bucket-test");
    Couchbase::Client h(connstr, "shan1123", "fog-ws");
    Couchbase::Client *h_ptr = &h;

    // connect() 
    Status rv = h.connect();

    // check error
    if(!rv.success())
    {
        cout << "Couldn't connect to '" << connstr <<"'. " << endl;
        cout << "Reason: " << rv << endl;
        exit(EXIT_FAILURE);
    }

    // storeDoc()
    storeDoc(h_ptr);

    // getDoc()
    getDoc(h_ptr);

    // storeWall()
    //storeWall(h_ptr);

    return 0;
}
