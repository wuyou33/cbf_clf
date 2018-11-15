/************
 * Includes *
 ************/

// Standard Header Files
#include <iostream>
#include <stdio.h>
#include <string>
#include <array>
#include <cmath>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

#include <boost/thread/thread.hpp>

// Custom Header Files
#include "input_message_handler.h"

/*************
 * Variables *
 *************/
int loop_rate_ = 1; //Loop Rate of 10 Hz
ros::Subscriber pose;
std::string pose_algorithm = "zed";

// Pose Information
// double pose_tx, pose_ty, pose_tz; // Translations
// double pose_q_x, pose_q_y, pose_q_z, pose_q_w; // Quaternions
double pose_roll, pose_pitch, pose_yaw;
double pose_trans[3];
double pose_rot[3];

// Odometry Information
// double odom_tx, odom_ty, odom_tz; // Translations
// double odom_q_x, odom_q_y, odom_q_z, odom_q_w; // Quaternions
double odom_roll, odom_pitch, odom_yaw;
double odom_trans[3];
double odom_rot[3];


/*************
 * Functions *
 *************/
// void get_pose(std::string algorithm);
// void get_pose(std::string algorithm){
//     std::tie(pose_tx, pose_ty, pose_tz, pose_q_x, pose_q_y, pose_q_z, pose_q_w) = get_pose_Handler(algorithm);

//     tf2::Quaternion q(pose_q_x, pose_q_y, pose_q_z, pose_q_w);
//     tf2::Matrix3x3 m(q);
    
//     m.getRPY(pose_roll, pose_pitch, pose_yaw);

//     pose_trans[1] = pose_tx;
//     pose_trans[2] = pose_ty;
//     pose_trans[3] = pose_tz;
//     pose_rot[1] = pose_roll;
//     pose_rot[2] = pose_pitch;
//     pose_rot[3] = pose_yaw;

//     ROS_INFO("Pose is x: [%f], y: [%f], z: [%f], R: [%f], P: [%f], Y: [%f]",
//       pose_tx, pose_ty, pose_tz,
//       pose_roll, pose_pitch, pose_yaw);
// }