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
double pose_tx, pose_ty, pose_tz;
double pose_qx, pose_qy, pose_qz, pose_qw;
double pose_roll, pose_pitch, pose_yaw;

// Odometry Information
double odom_tx, odom_ty, odom_tz;
double odom_qx, odom_qy, odom_qz, odom_qw;
double odom_roll, odom_pitch, odom_yaw;


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
    odom_qx = msg->pose.pose.orientation.x;
    odom_qy = msg->pose.pose.orientation.y;
    odom_qz = msg->pose.pose.orientation.z;
    odom_qw = msg->pose.pose.orientation.w;
    tf2::Quaternion q(odom_qx, odom_qy, odom_qz, odom_qw);

    // 3x3 Rotation matrix from quaternion
    tf2::Matrix3x3 m(q);

    // Roll Pitch and Yaw from rotation matrix
    m.getRPY(odom_roll, odom_pitch, odom_yaw);
}

void zed_pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg) {

    // Camera position in map frame
    pose_tx = msg->pose.position.x;
    pose_ty = msg->pose.position.y;
    pose_tz = msg->pose.position.z;

    // Orientation quaternion
    pose_qx = msg->pose.orientation.x;
    pose_qy = msg->pose.orientation.y;
    pose_qz = msg->pose.orientation.z;
    pose_qw = msg->pose.orientation.w;
    tf2::Quaternion q(pose_qx, pose_qy, pose_qz, pose_qw);

    // 3x3 Rotation matrix from quaternion
    tf2::Matrix3x3 m(q);

    // Roll Pitch and Yaw from rotation matrix
    m.getRPY(pose_roll, pose_pitch, pose_yaw);
}