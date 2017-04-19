//inventory_control_client
//create by Bruce Mingxin Liu

#include <ros/ros.h>
//#include "BinManger.h"
#include <cwru_ariac/Part.h>
#include <cwru_ariac/InventoryServiceMsg.h>
#include "CameraEstimator.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char **argv){

	ros::init(argc, argv, "inventory_control_client");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<cwru_ariac::InventoryServiceMsg>("look_up_parts_space");
	cwru_ariac::InventoryServiceMsg srv;
	string part_name;

	while (ros::ok()){
            for(geometry_msgs::PoseStamped pose : srv.response.poses)
            {
		cout<<endl;
		cout<<"What's the part's name that has the highest priority? ";
		cin>>part_name;
		srv.request.part_name = part_name;// the name of the part is sending to the service to check spacial avaliablity
		if(client.call(srv)){
			cout << "the x coordinate is " << pose.pose.position.x << "and the y coordinate is" << pose.pose.position.y << endl;



		}
             }
	}


	return 0;

}
