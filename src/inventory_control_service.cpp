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

int 	counter = 0;
int     emptySpotCount;
double      half_bin_size = 0.3;            /* what is the bin size... */
double      r;                              /* radius of the priority part.. */


double      radius;

int k; 
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

char* 					defaultPartsNames[] = { "piston_rod_part", "gear_part", "pulley_part", "gasket_part",
                                       "part1",                  "part2",     "part3",   "part4" };
double     				defaultPartsSizes[8] =  { 0.059, 0.078425, 0.23392, 0.31442, 0.3, 0.06, 0.13,0.09};
std::vector<double>     Quadrant_bin1[4] = {{-0.85, -1.187 } ,{ -0.85, -1.474} ,{ -1.1404, -1.195}, {-1.1396, -1.4745}};
std::vector<double>     Quadrant_bin2[4] = {{-0.849, -0.382}, {-0.85, -0.688}, {-1.143 , -0.4009}, {-1.15, -0.685}};
std::vector<double>     Quadrant_bin3[4] = {{-1.1, 0.13}, {-1.1, 0.33}, {-0.9 , 0.33}, {-0.9, 0.13}};


std::pair<string, double> part_names[8];
    vector<Bin> bins;
    
   
bool callback( cwru_ariac::InventoryServiceMsgRequest & request, cwru_ariac::InventoryServiceMsgResponse & response )
{

	int index; 
    ROS_INFO( "callback activated" );
    string part_name( request.part_name );
 
    ROS_WARN("The size is %f", defaultPartsSizes[0]);
	ROS_WARN("The bin size is %f", Quadrant_bin1[3][0]);

    for ( k = 0; k < 7; k++ )
    {
        if ( part_name.compare( defaultPartsNames[k] ) == 0 )
        {
            r   = defaultPartsSizes[k];
            double test = pow(r,2.0);
            ROS_INFO("The square of radius is %f", test);
     		index = k; 
     		ROS_INFO("The radius is %f", r);//this is working!!!
     		break;

            // ROS_INFO("The part size is recorded as: %d", r);
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

    	

     	if(index == 2){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin2[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin2[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)) // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin2[i][0];
					response.pose_y = Quadrant_bin2[i][1];
     		}


     	}


			// for(i = 0; i <= 3; i++){
	  //           if( abs(Quadrant_bin2[i][0] - part.pose.pose.position.x) > abs(defaultPartsSizes[k]) + abs(r)){
	  //           response.pose_x =  Quadrant_bin2[i][0];
	  //           ROS_WARN("X IS so WORKING");
	  //           ROS_INFO("The part num is %d", k);
	  //           ROS_INFO("The size is %d", defaultPartsSizes[0]);
	  //           ROS_INFO("The bin size is %d", Quadrant_bin1[3][0]);
	  //           ROS_INFO("defaultPartsName is %s", defaultPartsNames[0]);

	  //           counter = counter + 1;
			// 	}
			// 	}
	   

   //     		for(i = 0; i <= 3; i++){
	  //           if( abs(Quadrant_bin2[i][1] - part.pose.pose.position.y) > abs(defaultPartsSizes[k]) + abs(r)){
	  //           response.pose_y = Quadrant_bin2[i][1];
	  //           ROS_WARN("Y IS so WORKING!!!");
	  //     		}
			// 	}
		//	}
    
    		 
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
