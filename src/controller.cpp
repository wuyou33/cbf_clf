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

  ROS_WARN("Starting controller.cpp");

  //Initizializing a ROS-node called "cbf_clf_controller"
	ros::init(argc, argv, "cbf_clf_controller");
  ros::NodeHandle node;

  ros::Rate loop_rate(10); //Needs to be declared AFTER the NodeHandle !

  ROS_WARN("Starting while loop in controller.cpp");
  while (ros::ok())
  {
    
    // Update pose information
    ROS_WARN("Update pose information");
    ros::Subscriber zedPose = node.subscribe("/zed/pose", 10, zed_pose_Callback);

    ROS_WARN("Publish pose data");
    ROS_WARN("pose x: [%f], y: [%f], z: [%f]", pose_tx, pose_ty, pose_tz);

    ros::spinOnce();
    loop_rate.sleep();
  }


    return 0;
}