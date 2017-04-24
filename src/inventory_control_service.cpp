/* create by Bruce Mingxin Liu on Apirl 15th 2017, 4:47 pm */

#include <ros/ros.h>
/* #include "BinManger.h" */
#include <cwru_ariac/Part.h>
#include <cwru_ariac/InventoryServiceMsg.h>
#include "CameraEstimator.h"
#include "AriacBase.h"
#include "BinManager.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;


bool        part_exists = true;        /* To check if the number of parts on the bin is the same as the proposed number */
int     TotalNumOfParts = 103;          /* the total number of parts or locations to put the parts. */
int     i;
int     emptySpotCount;
double      half_bin_size = 0.3;            /* what is the bin size... */
double      r;                              /* radius of the priority part.. */
double      x;
double      y;
double      radius;
int     k;

CameraEstimator *camera_ptr;


std::vector<double>     part_size;
double _xPose;
double  _yPose;
double _zPose;

geometry_msgs::Pose  _x_Pose;
geometry_msgs::Pose  _y_Pose;

geometry_msgs::Pose  part;
geometry_msgs::PoseStamped  defaultBin;
geometry_msgs::PoseStamped  locations;

const string            defaultPartsNames[totalPartsTypes] = { "piston_rod_part", "gear_part", "pulley_part", "gasket_part",
                                       "part1",                  "part2",     "part3",   "part4" };
const double            defaultPartsSizes[totalPartsTypes][2] = { { 0.059, 0.052 }, { 0.078425, 0.078425 }, { 0.23392, 0.23392 }, { 0.31442, 0.15684 },
                                      { 0.3,   0.1   }, { 0.06, 0.015    }, { 0.13,    0.07    }, { 0.09,    0.06    } };


std::pair<string, double> part_names[8];
    vector<Bin> bins;
    
   
bool callback( cwru_ariac::InventoryServiceMsgRequest & request, cwru_ariac::InventoryServiceMsgResponse & response )
{
    /* for (bin[0]; bin[i]; i++){ // loop to check from first bin to the last */
    ROS_INFO( "callback activated" );
    string part_name( request.part_name );
   


    for ( i = 0; i < 7; i++ )
    {
        if ( part_name.compare( defaultPartsName[i] ) == 1 )
        {
            x   = defaultPartsSizes[i][1];
            y   = defaultPartsSizes[i][2];
        }

    camera_ptr->ForceUpdate();

    // for ( auto part : camera_ptr->inView )
    // {
    //     ROS_INFO_STREAM( "This is pose stamped of each part:\n" << part.pose ); /* also equal to outPose */
    //     ROS_INFO_STREAM( "This is pose of each part:\n" << part.pose.pose );
    //     ROS_INFO_STREAM( "This is the name of each part:\n" << part.name );
    // }

     auto part_list = findPart(camera_ptr->inView, part_name);
     for (auto part : part_list) {
        //response.poses.push_back(part.pose);
        part.pose.pose.position.x = _xPose;
        part.pose.pose.position.y = _yPose;
        part.pose.pose.position.z = _zPose;
        for (i = 0; i < 7; i++)
        {
        if(bins[i].pose.pose.position.x - 0.01 <= _xPose <= bins[i].pose.pose.position.x + 0.01 && bins[i].pose.pose.position.y - 0.01 <= _yPose <= bins[i].pose.pose.position.y + 0.01 && bins[i].pose.pose.position.z - 0.01 <= _zPose <= bins[i].pose.pose.position.z + 0.01){
           part_exists = true;
       }
           else{
            if(x<= defaultPartsSizes[totalPartsTypes][2][1] && y <= defaultPartsSizes[totalPartsTypes][2][2]){
                part_exists = false;
                response.pose_x = bins[i].pose.pose.position.x;
                response.pose_y = bins[i].pose.pose.position.y;
                response.pose_z = bins[i].pose.pose.position.z;
            }
           }
        
    }
     // matchPose(part.pose, camera_ptr->binBoundBox[7].Xmin);

        if(camera_ptr->onBin[1].size() == 0){
       
         response.num = 2; 
         response.emptybin = true;
     }
     }
}


int main( int argc, char** argv )
{
    ros::init( argc, argv, "inventory_control_service" );
    ros::NodeHandle     nh;
    ros::ServiceServer  service = nh.advertiseService( "look_up_parts_space", callback );

    CameraEstimator camera( nh, "/ariac/logical_camera_1" );

    camera_ptr = &camera;

    camera.ForceUpdate();



    ROS_INFO( "THIS IS A TEST" );
   
    // for ( auto part : camera.inView )
    // {
    //     ROS_INFO_STREAM( "This is pose stamped of each part:\n" << part.pose ); /* also equal to outPose */
    //     ROS_INFO_STREAM( "This is pose of each part:\n" << part.pose.pose );
    //     ROS_INFO_STREAM( "This is the name of each part:\n" << part.name );
    //     part.pose.pose.position.x;
    // }


    ROS_INFO( "Ready to look up parts." );


    ros::spin();
    return(0);
}
