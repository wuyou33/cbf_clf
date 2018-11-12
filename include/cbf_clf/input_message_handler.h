/****************
 * Header Files *
 ****************/
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>

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


/*************
 * Variables *
 *************/
//ZED Subscriber Callbacks

void zed_odom_Callback(const nav_msgs::Odometry::ConstPtr& msg) {

    // Camera position in map frame
    odom_tx = msg->pose.pose.position.x;
    odom_ty = msg->pose.pose.position.y;
    odom_tz = msg->pose.pose.position.z;

    // Orientation quaternion
    tf2::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);

    // 3x3 Rotation matrix from quaternion
    tf2::Matrix3x3 m(q);

    // Roll Pitch and Yaw from rotation matrix
    m.getRPY(odom_roll, odom_pitch, odom_yaw);

    // // Output the measure
    // ROS_INFO("Received odom in '%s' frame : X: %.2f Y: %.2f Z: %.2f - R: %.2f P: %.2f Y: %.2f",
    //          msg->header.frame_id.c_str(),
    //          tx, ty, tz,
    //          roll * RAD2DEG, pitch * RAD2DEG, yaw * RAD2DEG);
}

void zed_pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg) {

    // Camera position in map frame
    pose_tx = msg->pose.position.x;
    pose_ty = msg->pose.position.y;
    pose_tz = msg->pose.position.z;

    // Orientation quaternion
    tf2::Quaternion q(
        msg->pose.orientation.x,
        msg->pose.orientation.y,
        msg->pose.orientation.z,
        msg->pose.orientation.w);

    // 3x3 Rotation matrix from quaternion
    tf2::Matrix3x3 m(q);

    // Roll Pitch and Yaw from rotation matrix
    m.getRPY(pose_roll, pose_pitch, pose_yaw);

    // // Output the measure
    // ROS_INFO("Received pose in '%s' frame : X: %.2f Y: %.2f Z: %.2f - R: %.2f P: %.2f Y: %.2f",
    //          msg->header.frame_id.c_str(),
    //          tx, ty, tz,
    //          roll * RAD2DEG, pitch * RAD2DEG, yaw * RAD2DEG);
}
