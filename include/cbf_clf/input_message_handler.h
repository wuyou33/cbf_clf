#ifndef INPUT_MESSAGE_HANDLER_H_INCLUDED
#define INPUT_MESSAGE_HANDLER_H_INCLUDED
/************
 * Includes *
 ************/
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>
#include <tuple>
#include <array>
#include "ros/ros.h"

#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

/*************
 * Variables *
 *************/
#define RAD2DEG 57.295779513
// Pose Information
double pose_tx, pose_ty, pose_tz; // Translations
double pose_q_x, pose_q_y, pose_q_z, pose_q_w; // Quaternions

// Odometry Information
double odom_tx, odom_ty, odom_tz;
double odom_q_x, odom_q_y, odom_q_z, odom_q_w; // Quaternions


/*************
 * Functions *
 *************/

//ZED Subscriber Callbacks
void zed_odom_Callback(const nav_msgs::Odometry::ConstPtr& msg) {

    // Camera position in map frame
    odom_tx = msg->pose.pose.position.x;
    odom_ty = msg->pose.pose.position.y;
    odom_tz = msg->pose.pose.position.z;

    // Orientation quaternion
    odom_q_x = msg->pose.pose.orientation.x;
    odom_q_y = msg->pose.pose.orientation.y;
    odom_q_z = msg->pose.pose.orientation.z;
    odom_q_w = msg->pose.pose.orientation.w;
}

void zed_pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg) {

    // Camera position in map frame
    pose_tx = msg->pose.position.x;
    pose_ty = msg->pose.position.y;
    pose_tz = msg->pose.position.z;

    // Orientation quaternion
    pose_q_x = msg->pose.orientation.x;
    pose_q_y = msg->pose.orientation.x;
    pose_q_z = msg->pose.orientation.x;
    pose_q_w = msg->pose.orientation.x;

    ROS_WARN("Got some numbers: [%f], [%f], [%f], [%f], [%f], [%f], [%f]", pose_tx, pose_ty, pose_tz, pose_q_x, pose_q_y, pose_q_z, pose_q_w);
}


// General Functions

// The function get_pose returns a tuple containing the current pose
// std::tuple<double, double, double, double, double, double, double> get_pose_Handler(std::string algorithm);

// General Functions

// The function get_pose returns a tuple containing the current pose
// The tuple is made from:
// vector of doubles: pose_trans = {pose_tx, pose_ty, pose_tz}
// vector of doubles: pose_rot = {pose_roll, pose_pitch, pose_yaw}
// tf::Quaternion: q
// tf::Matrix3x3: m = m(q)
std::tuple<double, double, double, double, double, double, double> get_pose_Handler(std::string algorithm){
    ros::Subscriber zedPose;
    ros::NodeHandle node_get_pose;

    if (algorithm == "zed"){
    zedPose = node_get_pose.subscribe("/zed/pose", 1000, zed_pose_Callback);
    ROS_INFO("Got some more numbers: [%f], [%f], [%f], [%f], [%f], [%f], [%f]", pose_tx, pose_ty, pose_tz, pose_q_x, pose_q_y, pose_q_z, pose_q_w);
    ros::spinOnce();
    }
    // else if (alogrithm == "other"){
    
    // // TODO

    // }
    else{
        ROS_ERROR("The called pose algortihm is not valid!");
    }

    return std::make_tuple(pose_tx, pose_ty, pose_tz, pose_q_x, pose_q_y, pose_q_z, pose_q_w);
}

#endif