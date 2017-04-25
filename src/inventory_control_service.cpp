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


double      radius;
int     k;

CameraEstimator *camera_ptr;


std::vector<double>     part_size;
double _xPose;
double  _yPose;
double _zPose;

double  _x_Pose;
geometry_msgs::Pose  _y_Pose;

geometry_msgs::Pose  part;
geometry_msgs::PoseStamped  defaultBin;
geometry_msgs::PoseStamped  locations;

const string            defaultPartsNames[totalPartsTypes] = { "piston_rod_part", "gear_part", "pulley_part", "gasket_part",
                                       "part1",                  "part2",     "part3",   "part4" };
const double            defaultPartsSizes[totalPartsTypes] =  { 0.059, 0.078425, 0.23392, 0.31442, 0.3, 0.06, 0.13,0.09};
std::vector<double>     Quadrant_bin1[4] = {{-0.85, -1.187 } ,{ -0.85, -1.474} ,{ -1.1404, -1.195}, {-1.1396, -1.4745}};
std::vector<double>     Quadrant_bin2[4] = {{-0.849, -0.382}, {-0.85, -0.688}, {-1.143 , -0.4009}, {-1.15, -0.685}};


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
            r   = defaultPartsSizes[i];
            k = i;
            //ROS_INFO("The part size is recorded as: %d", r);
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
    //     //response.poses.push_back(part.pose);
         // part.pose.pose.position.x = _xPose;
         // part.pose.pose.position.y = _yPose;
         // part.pose.pose.position.z = _zPose;
         ROS_INFO_STREAM(part.pose);
    //     for (i = 0; i < 7; i++)
    //     {
    //     if(bins[i].pose.pose.position.x - 0.05 <= _xPose <= bins[i].pose.pose.position.x + 0.05 && bins[i].pose.pose.position.y - 0.05 <= _yPose <= bins[i].pose.pose.position.y + 0.05 && bins[i].pose.pose.position.z - 0.05 <= _zPose <= bins[i].pose.pose.position.z + 0.05){
    //        part_exists = true;
    //    }
    //        else{
    //             part_exists = false;
    //             response.pose_x = bins[i].pose.pose.position.x;
    //             response.pose_y = bins[i].pose.pose.position.y;
    //             response.pose_z = bins[i].pose.pose.position.z;
    //        }
        
    // }
    //  // matchPose(part.pose, camera_ptr->binBoundBox[7].Xmin);

    //     if(camera_ptr->onBin[1].size() == 0){
    //     // response.poses.push_back(part.pose);
    //      response.num = 2; 
    //      response.emptybin = true;
    //  }
  response.pose_x = part.pose.pose.position.x;
    
     
       for(i = 0; i <= 1; i++){
            if( abs(Quadrant_bin2[i][0] - part.pose.pose.position.x) > abs(defaultPartsSizes[k]) + abs(r)){
            response.pose_x =  Quadrant_bin2[i][0];
            ROS_WARN("X IS WORKING");
        }
        }    

       for(i = 0; i <= 1; i++){
            if( abs(Quadrant_bin2[i][1] - part.pose.pose.position.y) > abs(defaultPartsSizes[k]) + abs(r)){
            response.pose_y = Quadrant_bin2[i][1];
            ROS_WARN("Y IS WORKING!!!");
        }
    }
    
     ros::spinOnce();
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
