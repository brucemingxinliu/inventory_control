//inventory_control_client
//create by Bruce Mingxin Liu

#include <ros/ros.h>
#include "BinManger.h"
#include <cwru_ariac/Part.h>
#include <inventory_control_service/InventoryServiceMsg.h>
#include "CameraEstimator.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char **argv){

	ros::int(argc, argv, "inventory_control_client");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<inventory_control_service::InventoryServiceMsg>("look_up_parts_space");
	inventory_control_service::InventoryServiceMsg srv;
	String part_name;

	while (ros::ok()){
		cout<<endl;
		cout<<"What's the part's name that has the highest priority? ";
		cin>>part_name;
		srv.request.part_name = part_name;// the name of the part is sending to the service to check spacial avaliablity
		if(client.call(srv)){
			cout << "the x coordinate is " << srv.response.location_x << "and the y coordinate is" << srv.response.location_y << endl;



		}
	}


	return 0;

}
