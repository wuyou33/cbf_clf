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

int main(int argc, char** argv){

  //Initizializing a ROS-node called "cbf_clf_controller"
	ros::init(argc, argv, "cbf_clf_controller");
  ros::NodeHandle node;

  ros::Rate loop_rate(loop_rate_); //Needs to be declared AFTER the NodeHandle !

  // if (pose_algorithm == "zed"){
    poseSubscriber = node.subscribe("/zed/pose", 1000, zed_pose_Callback);
    ROS_INFO("Got some more numbers: [%f], [%f], [%f], [%f], [%f], [%f], [%f]", pose_tx, pose_ty, pose_tz, pose_q_x, pose_q_y, pose_q_z, pose_q_w);
  // }
  // else if (pose_algorithm == "other"){
  //   // TODO
  // }
  // else{
  //  ROS_ERROR("The called pose algortihm is not valid!");
  // }

  // tf2::Quaternion q(pose_q_x, pose_q_y, pose_q_z, pose_q_w);
  // tf2::Matrix3x3 m(q);

  // m.getRPY(pose_roll, pose_pitch, pose_yaw);

  ROS_INFO("Pose is x: [%f], y: [%f], z: [%f], R: [%f], P: [%f], Y: [%f]",
    pose_tx, pose_ty, pose_tz,
    pose_roll, pose_pitch, pose_yaw);

  // boost::this_thread::sleep(boost::posix_time::seconds(1));
    
  ros::spin();
  // loop_rate.sleep();
  return 0;
}
