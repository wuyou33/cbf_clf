// Standard Header Files
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

/*************
 * Variables *
 *************/
#define RAD2DEG 57.295779513
// Pose Information
double pose_tx;
double pose_ty;
double pose_tz;
double pose_roll;
double pose_pitch;
double pose_yaw;

// Odometry Information
double odom_tx;
double odom_ty;
double odom_tz;
double odom_roll;
double odom_pitch;
double odom_yaw;


// Custom Header Files
//#include "input_message_handler.h"

// Variables
int loop_rate_ = 1; //Loop Rate of 10 Hz
ros::Subscriber zedPose;

// Functions
// void zed_pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
//     ROS_WARN("Called Calback Function successful");

//     // Camera position in map frame
//     pose_tx = msg->pose.position.x;
//     pose_ty = msg->pose.position.y;
//     pose_tz = msg->pose.position.z;
//     ROS_WARN("Calculated pose_tx,y,z");

//     // Orientation quaternion
//     tf2::Quaternion q(
//         msg->pose.orientation.x,
//         msg->pose.orientation.y,
//         msg->pose.orientation.z,
//         msg->pose.orientation.w);
//     ROS_WARN("Calculated pose_qx,y,z");

//     // 3x3 Rotation matrix from quaternion
//     tf2::Matrix3x3 m(q);
//     ROS_WARN("Calculated m(q)");

//     // Roll Pitch and Yaw from rotation matrix
//     m.getRPY(pose_roll, pose_pitch, pose_yaw);
//     ROS_WARN("Calculated R(q)");

//     // Output the measure
//     ROS_INFO("Received pose in '%s' frame : X: %.2f Y: %.2f Z: %.2f - R: %.2f P: %.2f Y: %.2f",
//              msg->header.frame_id.c_str(),
//              pose_tx, pose_ty, pose_tz,
//              pose_roll * RAD2DEG, pose_pitch * RAD2DEG, pose_yaw * RAD2DEG);
// }