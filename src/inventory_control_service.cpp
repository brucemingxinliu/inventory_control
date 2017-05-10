/* create by Bruce Mingxin Liu on Apirl 15th 2017, 4:47 pm */
//last update: May 10th, 2017 12:14pm

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

char* 					defaultPartsNames[] = { "piston_rod_part", "gear_part", "pulley_part", "gasket_part", "part_1" , "part_2", "part_3", "part_4"};
double     				defaultPartsSizes[8] =  { 0.059, 0.078425, 0.23392, 0.31442, 0.3, 0.06, 0.13,0.09};
std::vector<double>     Quadrant_bin1[4] = {{-0.85, -1.187 } ,{ -0.85, -1.474} ,{ -1.1404, -1.195}, {-1.1396, -1.4745}};
std::vector<double>     Quadrant_bin2[4] = {{-0.849, -0.382}, {-0.85, -0.688}, {-1.143 , -0.4009}, {-1.15, -0.685}};
std::vector<double>     Quadrant_bin3[4] = {{-1.1, 0.13}, {-1.1, 0.33}, {-0.9 , 0.33}, {-0.9, 0.13}};
std::vector<double>     Quadrant_bin4[4] = {{-0.85, 0.845}, {-0.85, 1.145}, {-1.15 , 1.145}, {-1.15, 0.845}};
std::vector<double>     Quadrant_bin5[4] = {{-0.4516, -1.4763}, {-0.440307, -1.21}, {-0.16076 , -1.2188}, {-0.166033, -1.4832}};
std::vector<double>     Quadrant_bin6[4] = {{-0.150491, -0.680682}, {-0.43547, -0.690350}, {-0.424199 , -0.339663}, {-0.145492, -0.35243}};
std::vector<double>     Quadrant_bin7[4] = {{-0.1513, 0.35374}, {-0.440257, 0.3479}, {-0.445276 , 0.010377}, {-0.144263, 0.028127}};
std::vector<double>     Quadrant_bin8[4] = {{-0.15, 1.143}, {-0.45, 1.1453}, {-0.45 , 0.845}, {-0.15, 0.845}};


    
   
bool callback( cwru_ariac::InventoryServiceMsgRequest & request, cwru_ariac::InventoryServiceMsgResponse & response)
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

  
        }
    }

    camera_ptr->ForceUpdate();
    
 

     auto part_list = findPart(camera_ptr->inView, part_name);
     for (auto part : part_list) {



     	  if(index == 1){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin1[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin1[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin1[i][0];
					response.pose_y = Quadrant_bin1[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}

    	  if(index == 2){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin2[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin2[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin2[i][0];
					response.pose_y = Quadrant_bin2[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}


  		if(index == 3){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin3[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin3[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin3[i][0];
					response.pose_y = Quadrant_bin3[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}

     	if(index == 4){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin4[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin4[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin4[i][0];
					response.pose_y = Quadrant_bin4[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}

     	if(index == 5){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin5[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin5[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin5[i][0];
					response.pose_y = Quadrant_bin5[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}

     	if(index == 6){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin6[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin6[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin6[i][0];
					response.pose_y = Quadrant_bin6[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}

     	if(index == 7){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin7[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin7[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin7[i][0];
					response.pose_y = Quadrant_bin7[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}

     	if(index == 8){
     		for(int i = 0; i<=3; i++){
     			if(  pow((Quadrant_bin8[i][0] - part.pose.pose.position.x), 2.0) + pow((Quadrant_bin8[i][1] - part.pose.pose.position.y), 2.0) > pow(r, 2.0)){ // The checking distance should be larger than the radius of the part
					
					response.pose_x = Quadrant_bin8[i][0];
					response.pose_y = Quadrant_bin8[i][1];
				}

					else{ 
							response.pose_x = 0.0;
							response.pose_y = 0.0;
						}
     		}


     	}

    		 
}

}


int main( int argc, char** argv )
{
    ros::init( argc, argv, "inventory_control_service" );
    ros::NodeHandle     nh;
    ros::ServiceServer  service = nh.advertiseService( "look_up_parts_space", callback );

    CameraEstimator camera( nh, "/ariac/logical_camera_1" );//Here can be edited to subscribe to more cameras. Ideally one camera for each bin

    camera_ptr = &camera;
    camera.ForceUpdate();

    ROS_INFO( "Ready to look up parts." );


    ros::spin();
    return(0);
}
