/************
 * Includes *
 ************/
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>
#include <tuple>

#include "std_msgs/String.h"

#include "ros/ros.h"

#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"
#include "cbf_clf/srv_get_pose.h"

// Custom Header Files
#include "cbf_clf/input_message_handler.h"
#include "cbf_clf/output_message_handler.h"

/*************
 * Variables *
 *************/
ros::Subscriber zedPose;
ros::ServiceClient client_get_pose;
int loop_rate_ = 1; //Loop Rate of 10 Hz

// Pose Information
double pose_tx, pose_ty, pose_tz;
double pose_qx, pose_qy, pose_qz, pose_qw;
double pose_roll, pose_pitch, pose_yaw;
tf2::Quaternion pose_q(1, 0, 0, 0);
tf2::Matrix3x3 pose_m(pose_q);

// Odometry Information
double odom_tx, odom_ty, odom_tz;
double odom_qx, odom_qy, odom_qz, odom_qw;
double odom_roll, odom_pitch, odom_yaw;
tf2::Quaternion odom_q(1, 0, 0, 0);
tf2::Matrix3x3 odom_m(odom_q);

/*************
 * Functions *
 *************/
 void get_pose(ros::NodeHandle node){
    cbf_clf::srv_get_pose srv_res;

    client_get_pose = node.serviceClient<cbf_clf::srv_get_pose>("srv_get_pose");

    pose_tx = srv_res.response.x;
    pose_ty = srv_res.response.y;
    pose_tz = srv_res.response.z;
    pose_qx = srv_res.response.qx;
    pose_qy = srv_res.response.qy;
    pose_qz = srv_res.response.qz;
    pose_qw = srv_res.response.qw;

    // tf2::Quaternion pose_q(pose_qx, pose_qy, pose_qz, pose_qw);
    // tf2::Matrix3x3 pose_m(pose_q);
    tf2::Quaternion pose_q(pose_qx, pose_qy, pose_qz, pose_qw);
    tf2::Matrix3x3 pose_m(pose_q);
    
    pose_m.getRPY(pose_roll, pose_pitch, pose_yaw);
}