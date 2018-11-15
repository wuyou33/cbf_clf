/*
* Workflow for Controller
* 1) Get pose data
* 2) Get depth map
* 2.1) calculate safe space from depth map
* 3) Define Control Barrier Function (CBF)
* 3.1) Define first derivitave of CBF
* 4) Define Control Lyapunov Function (CLF)
* 4.1) Define first derivitave of CLF
* 5) Define 
* 
* 
*/

#include "../include/cbf_clf/controller.h"

//using namespace std;

int main(int argc, char** argv)
{

  //Initizializing a ROS-node called "cbf_clf_controller"
	ros::init(argc, argv, "controller");
  ros::NodeHandle node;

  ros::Rate loop_rate(loop_rate_); //Needs to be declared AFTER the NodeHandle !


  //while (ros::ok())
  //{
    
    // Update pose information
    // ros::Subscriber zedPose = node.subscribe("/zed/pose", 1000, zed_pose_Callback);
    zedPose = node.subscribe("/zed/pose", 1000, zed_pose_Callback);

    ros::spin();
    //loop_rate.sleep();
  //}


    return 0;
}