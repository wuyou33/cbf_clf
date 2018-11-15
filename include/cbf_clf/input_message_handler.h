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

ros::Subscriber get_Pose;

#define RAD2DEG 57.295779513
// Pose Information
double pose_tx, pose_ty, pose_tz; // Translations
double pose_q_x, pose_q_y, pose_q_z, pose_q_w; // Quaternions
double pose_roll, pose_pitch, pose_yaw; //Rotations

// Odometry Information
double odom_tx, odom_ty, odom_tz; // Translations
double odom_q_x, odom_q_y, odom_q_z, odom_q_w; // Quaternions
double odom_roll, odom_pitch, odom_yaw; //Rotations


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

    ROS_WARN("Got some numbers: [%f], [%f], [%f], [%f], [%f], [%f], [%f]", pose_tx, pose_ty, pose_tz, pose_q_x, pose_q_y, pose_q_z, pose_q_w);
}