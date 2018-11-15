/************
 * Includes *
 ************/
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"

// Custom Header Files
#include "input_message_handler.h"

/*************
 * Variables *
 *************/
ros::Subscriber zedPose;
int loop_rate_ = 10; //Loop Rate of 10 Hz

// Pose Information
extern double pose_tx, pose_ty, pose_tz;
extern double pose_qx, pose_qy, pose_qz, pose_qw;
extern double pose_roll, pose_pitch, pose_yaw;

// Odometry Information
extern double odom_tx, odom_ty, odom_tz;
extern double odom_qx, odom_qy, odom_qz, odom_qw;
extern double odom_roll, odom_pitch, odom_yaw;

/*************
 * Functions *
 *************/