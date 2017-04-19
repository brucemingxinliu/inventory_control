//create by Bruce Mingxin Liu on Apirl 15th 2017, 4:47 pm

#include <ros/ros.h>
//#include "BinManger.h"
#include <cwru_ariac/Part.h>
#include <cwru_ariac/InventoryServiceMsg.h>
#include "CameraEstimator.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;


bool part_exists = false; // To check if the number of parts on the bin is the same as the proposed number
int TotalNumOfParts = 103; // the total number of parts or locations to put the parts.
int i;
int emptySpotCount;
double half_bin_size = 0.3; // what is the bin size...
double r; // radius of the priority part..
double x;
double y;
double radius;
int k;
std::list<int> spot;

geometry_msgs::PoseStamped _xPose;
geometry_msgs::PoseStamped _yPose;
geometry_msgs::PoseStamped _x_Pose;
geometry_msgs::PoseStamped _y_Pose;


std::pair<string, double> part_names[8];

//cameraSubscriber = nh_.subscribe(topic, 10, &CameraEstimator::cameraCallback, this);

bool callback(cwru_ariac::InventoryServiceMsgRequest& request, cwru_ariac::InventoryServiceMsgResponse& response){
//for (bin[0]; bin[i]; i++){ // loop to check from first bin to the last
    ROS_INFO("callback activated");
    string part_name(request.part_name);
    for(i = 0; i < 7; i++){
        if(part_name.compare(part_names[i].first) == 1){
            radius = part_names[i].second;
        }

    }

    for (int j = 0; j < TotalNumOfParts; j++){ // loop to check each location on each bin
    	if(part.traceable = false && nextPart.traceable = true){
    		part_exists = true;
    		emptySpotCount = emptySpotCount + 1;
    		part.pose.pose.position.x.push_back(_xPose);
    		part.pose.pose.position.y.push_back(_yPose);
    		next.Part.linear.x.push_back(_x_Pose); 
            next.Part.linear.y.push_back(_y_Pose);
            spot.push_back(j); // saving all radius of the locations

    	}

    }


    for (i = 0; i <= emptySpotCount; ++i){ // collision check
    	/*if(PoseStamped_xPose(i) > bins[i].pose.pose.position.x + half_bin_size && PoseStamped_xPose(i) < part.pose.pose.position.x - half_bin_size){

    		if (PoseStamped_yPose(i) > part.pose.pose.position.y + half_bin_size && PoseStamped_yPose(i) < part.pose.pose.position.y - half_bin_size){
    			return bins[i].name; //checking what are the parts should be on this specific bin then check the spatial avaliability
    			int ptr = i;
    			x = PoseStamped_xPose(i);
    			y = PoseStamped_yPose(i);

    		}*/
            for( k = 0; k <= spot.size() ; k++){}
    		if(abs(_xPose(k) - _x_Pose(k)) < radius + (double)(spot(k)) && abs(_yPose(k) - _y_Pose(k)) < radius + (double)(spot(k))){ 
    			ROS_WARN("The current locations are: x = %d  y = %d", x , y);
                x = _xPose.pose.position.x;
                y = _yPose.pose.position.y;
                geometry_msgs::PoseStamped response_pose;
                response_pose.pose.position.x = x;
                response_pose.pose.position.y = y;
                reponse.pose.push_back(response_pose);
    		}
    	}
    }
    }
}
    int main(int argc, char** argv){
        ros::init(argc, argv, "inventory_control_service");
        ros::NodeHandle nh;
        ros::ServiceServer service = nh.advertiseService("look_up_parts_space",callback); 
        ros::Subscriber subscriber = nh.subscribe("/ariac/logical_camera_1", 10, callback);
        ROS_INFO("Ready to look up parts.");
        part_names[0].first = "piston_rod_part_1"; // Bin1.. 12
	part_names[0].second = 0.06;

	part_names[1].first = "Pulley_part_1"; //Bin2 .. 4
	part_names[1].second = 0.12;

	part_names[2].first = "Gear_part"; //Bin3..25
	part_names[2].second = 0.03;

	part_names[3].first = "gasket_part"; //Bin4 .. 4
	part_names[3].second = 0.1;

	part_names[4].first = "Part_4"; // Bin5 .. 25
	part_names[4].second = 0.03;

	part_names[5].first = "Part_3"; // Bin6 .. 12
	part_names[5].second = 0.06;

	part_names[6].first = "piston_rod_part_2"; // Bin7.. 12
	part_names[6].second = 0.06;

	part_names[7].first = "Pulley_part_2"; //Bin2 .. 4
	part_names[7].second = 0.12;
//BinManager::BinManager(ros::NodeHandle nodeHandle){ // constructor of BinManager
//BinManger.assignCamera(); // Call the logic camera

}
for (int i = 0; i < totalBins; ++i) {
        bins.push_back(defaultBin);

}

        bins[0].name = "Bin4";
        bins[0].priority = 6.0;
        bins[0].pose.pose.position.x = -1.000000;
        bins[0].pose.pose.position.y = 0.995000;
        bins[0].pose.pose.position.z = 0.0;

        bins[1].name = "Bin8";
        bins[1].priority = 10.0;
        bins[1].pose.pose.position.x = -0.300000;
        bins[1].pose.pose.position.y = 0.995000;
        bins[1].pose.pose.position.z = 0.0;

        bins[2].name = "Bin3";
        bins[2].priority = 4.0;
        bins[2].pose.pose.position.x = -1.000000;
        bins[2].pose.pose.position.y = 0.230000;
        bins[2].pose.pose.position.z = 0.0;

        bins[3].name = "Bin7";
        bins[3].priority = 8.0;
        bins[3].pose.pose.position.x = -0.300000;
        bins[3].pose.pose.position.y = 0.230000;
        bins[3].pose.pose.position.z = 0.0;
   
        bins[4].name = "Bin2";
        bins[4].priority = 3.0;
        bins[4].pose.pose.position.x = -1.000000;
        bins[4].pose.pose.position.y = -0.535000;
        bins[4].pose.pose.position.z = 0.0;

        bins[5].name = "Bin6";
        bins[5].priority = 7.0;
        bins[5].pose.pose.position.x = -0.300000;
        bins[5].pose.pose.position.y = -0.535000;
        bins[5].pose.pose.position.z = 0.0;

        bins[6].name = "Bin1";
        bins[6].priority = 5.0;
        bins[6].pose.pose.position.x = -1.000000;
        bins[6].pose.pose.position.y = -1.330000;
        bins[6].pose.pose.position.z = 0.0;
 
        bins[7].name = "Bin5";
        bins[7].priority = 9.0;
        bins[7].pose.pose.position.x = -0.300000;
        bins[7].pose.pose.position.y = -1.330000;
        bins[7].pose.pose.position.z = 0.0;

        ros::spin();
        return 0;

    }

