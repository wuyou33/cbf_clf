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

void zed_pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    ROS_WARN("Called Calback Function successful");

    // Camera position in map frame
    pose_tx = msg->pose.position.x;
    pose_ty = msg->pose.position.y;
    pose_tz = msg->pose.position.z;
    ROS_WARN("Calculated pose_tx,y,z");

    // Orientation quaternion
    tf2::Quaternion q(
        msg->pose.orientation.x,
        msg->pose.orientation.y,
        msg->pose.orientation.z,
        msg->pose.orientation.w);
    ROS_WARN("Calculated pose_qx,y,z");

    // 3x3 Rotation matrix from quaternion
    tf2::Matrix3x3 m(q);
    ROS_WARN("Calculated m(q)");

    // Roll Pitch and Yaw from rotation matrix
    m.getRPY(pose_roll, pose_pitch, pose_yaw);
    ROS_WARN("Calculated R(q)");

    // Output the measure
    ROS_INFO("Received pose in '%s' frame : X: %.2f Y: %.2f Z: %.2f - R: %.2f P: %.2f Y: %.2f",
             msg->header.frame_id.c_str(),
             pose_tx, pose_ty, pose_tz,
             pose_roll * RAD2DEG, pose_pitch * RAD2DEG, pose_yaw * RAD2DEG);
}

int main(int argc, char** argv)
{

  ROS_WARN("Starting controller.cpp");

  //Initizializing a ROS-node called "cbf_clf_controller"
	ros::init(argc, argv, "cbf_clf_controller");
  ros::NodeHandle node;

  ROS_WARN("Sleep for 15 s");
  ros::Rate sleeptimer(1.0/15.0);
  sleeptimer.sleep();

  ros::Rate loop_rate(loop_rate_); //Needs to be declared AFTER the NodeHandle !

  ROS_WARN("Starting while loop in controller.cpp");
  //while (ros::ok())
  //{
    
    // Update pose information
    ROS_WARN("Update pose information");
    // ros::Subscriber zedPose = node.subscribe("/zed/pose", 1000, zed_pose_Callback);
    zedPose = node.subscribe("/zed/pose", 1000, zed_pose_Callback);
    ROS_WARN("pose x: [%f], y: [%f], z: [%f]", pose_tx, pose_ty, pose_tz);

    ros::spin();
    //loop_rate.sleep();
  //}


    return 0;
}

// void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {

//     // Camera position in map frame
//     double tx = msg->pose.pose.position.x;
//     double ty = msg->pose.pose.position.y;
//     double tz = msg->pose.pose.position.z;

//     // Orientation quaternion
//     tf2::Quaternion q(
//         msg->pose.pose.orientation.x,
//         msg->pose.pose.orientation.y,
//         msg->pose.pose.orientation.z,
//         msg->pose.pose.orientation.w);

//     // 3x3 Rotation matrix from quaternion
//     tf2::Matrix3x3 m(q);

//     // Roll Pitch and Yaw from rotation matrix
//     double roll, pitch, yaw;
//     m.getRPY(roll, pitch, yaw);

//     // Output the measure
//     ROS_INFO("Received odom in '%s' frame : X: %.2f Y: %.2f Z: %.2f - R: %.2f P: %.2f Y: %.2f",
//              msg->header.frame_id.c_str(),
//              tx, ty, tz,
//              roll * RAD2DEG, pitch * RAD2DEG, yaw * RAD2DEG);
// }

// void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {

//     // Camera position in map frame
//     double tx = msg->pose.position.x;
//     double ty = msg->pose.position.y;
//     double tz = msg->pose.position.z;

//     // Orientation quaternion
//     tf2::Quaternion q(
//         msg->pose.orientation.x,
//         msg->pose.orientation.y,
//         msg->pose.orientation.z,
//         msg->pose.orientation.w);

//     // 3x3 Rotation matrix from quaternion
//     tf2::Matrix3x3 m(q);

//     // Roll Pitch and Yaw from rotation matrix
//     double roll, pitch, yaw;
//     m.getRPY(roll, pitch, yaw);

//     // Output the measure
//     ROS_INFO("Received pose in '%s' frame : X: %.2f Y: %.2f Z: %.2f - R: %.2f P: %.2f Y: %.2f",
//              msg->header.frame_id.c_str(),
//              tx, ty, tz,
//              roll * RAD2DEG, pitch * RAD2DEG, yaw * RAD2DEG);
// }

// /**
//  * Node main function
//  */
// int main(int argc, char** argv) {
//     // Node initialization
//     ros::init(argc, argv, "zed_tracking_subscriber");
//     ros::NodeHandle n;

//     // Topic subscribers
//     ros::Subscriber subOdom    = n.subscribe("/zed/odom", 10, odomCallback);
//     ros::Subscriber subPose    = n.subscribe("/zed/pose", 10, poseCallback);

//     // Node execution
//     ros::spin();

//     return 0;
// }