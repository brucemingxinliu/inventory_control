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


bool        part_exists = false;        /* To check if the number of parts on the bin is the same as the proposed number */
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
BinManager *bin_ptr;

std::vector<double>     part_size;
geometry_msgs::PoseStamped  _xPose;
geometry_msgs::PoseStamped  _yPose;
geometry_msgs::PoseStamped  _x_Pose;
geometry_msgs::PoseStamped  _y_Pose;
geometry_msgs::PoseStamped  part;
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
    /* string abcd = camera.nextPart.name; */


    for ( i = 0; i < 7; i++ )
    {
        if ( part_name.compare( defaultPartsName[i] ) == 1 )
        {
            x   = defaultPartsSizes[i][1];
            y   = defaultPartsSizes[i][2];
        }
    }
//  response.poses.push_back(v);
    camera_ptr->ForceUpdate();

    // for ( auto part : camera_ptr->inView )
    // {
    //     ROS_INFO_STREAM( "This is pose stamped of each part:\n" << part.pose ); /* also equal to outPose */
    //     ROS_INFO_STREAM( "This is pose of each part:\n" << part.pose.pose );
    //     ROS_INFO_STREAM( "This is the name of each part:\n" << part.name );
    // }
     auto part_list = findPart(camera_ptr->inView, part_name);
     for (auto part : part_list) {
        matchPose(part.pose, bins[0].pose.pose);

        if(camera_ptr->onBin[1].size() == 0){
        // response.poses.push_back(part.pose);
         response.num = 2; 
         response.emptybin = true;
     }
     }



    for ( i = 0; i <= emptySpotCount; ++i ) /* collision check */
    { /*if(PoseStamped_xPose(i) > bins[i].pose.pose.position.x + half_bin_size && PoseStamped_xPose(i) < part.pose.pose.position.x - half_bin_size){
         *
         * if (PoseStamped_yPose(i) > part.pose.pose.position.y + half_bin_size && PoseStamped_yPose(i) < part.pose.pose.position.y - half_bin_size){
         * return bins[i].name; //checking what are the parts should be on this specific bin then check the spatial avaliability
         * int ptr = i;
         * x = PoseStamped_xPose(i);
         * y = PoseStamped_yPose(i);
         *
         * }*/
        /*for( k = 0; k <= spot.size() ; k++){}
         * if(abs(_xPose(k) - _x_Pose(k)) < radius + (double)(spot(k)) && abs(_yPose(k) - _y_Pose(k)) < radius + (double)(spot(k))){
         *  ROS_WARN("The current locations are: x = %d  y = %d", x , y);
         *  x = _xPose.pose.position.x;
         *  y = _yPose.pose.position.y;
         *  geometry_msgs::PoseStamped response_pose;
         *  response_pose.pose.position.x = x;
         *  response_pose.pose.position.y = y;
         *  reponse.pose.push_back(response_pose);
         * }*/
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

    bins[3].name = "Bin4";
    bins[3].priority = 6.0;
    bins[3].pose.pose.position.x = -1.000000;
    bins[3].pose.pose.position.y = 0.995000;
    bins[3].pose.pose.position.z = 0.0;

    bins[7].name = "Bin8";
    bins[7].priority = 10.0;
    bins[7].pose.pose.position.x = -0.300000;
    bins[7].pose.pose.position.y = 0.995000;
    bins[7].pose.pose.position.z = 0.0;

    bins[2].name = "Bin3";
    bins[2].priority = 4.0;
    bins[2].pose.pose.position.x = -1.000000;
    bins[2].pose.pose.position.y = 0.230000;
    bins[2].pose.pose.position.z = 0.0;

    bins[6].name = "Bin7";
    bins[6].priority = 8.0;
    bins[6].pose.pose.position.x = -0.300000;
    bins[6].pose.pose.position.y = 0.230000;
    bins[6].pose.pose.position.z = 0.0;

    bins[1].name = "Bin2";
    bins[1].priority = 3.0;
    bins[1].pose.pose.position.x = -1.000000;
    bins[1].pose.pose.position.y = -0.535000;
    bins[1].pose.pose.position.z = 0.0;

    bins[5].name = "Bin6";
    bins[5].priority = 7.0;
    bins[5].pose.pose.position.x = -0.300000;
    bins[5].pose.pose.position.y = -0.535000;
    bins[5].pose.pose.position.z = 0.0;

    bins[0].name = "Bin1";
    bins[0].priority = 5.0;
    bins[0].pose.pose.position.x = -1.000000;
    bins[0].pose.pose.position.y = -1.330000;
    bins[0].pose.pose.position.z = 0.0;

    bins[4].name = "Bin5";
    bins[4].priority = 9.0;
    bins[4].pose.pose.position.x = -0.300000;
    bins[4].pose.pose.position.y = -1.330000;
    bins[4].pose.pose.position.z = 0.0;

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
