/****************
 * Header Files *
 ****************/
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

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

/*************
 * Variables *
 *************/
#define RAD2DEG 57.295779513

ros::Subscriber subscriber_get_Pose;
ros::ServiceServer service_send_Pose;

std::string pose_algorithm = "zed";

int imh_loop_rate_ = 60;

// Pose Information
double imh_pose_tx, imh_pose_ty, imh_pose_tz;
double imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw;
double imh_pose_roll, imh_pose_pitch, imh_pose_yaw;

// Odometry Information
double imh_odom_tx, imh_odom_ty, imh_odom_tz;
double imh_odom_qx, imh_odom_qy, imh_odom_qz, imh_odom_qw;
double imh_odom_roll, imh_odom_pitch, imh_odom_yaw;

/*************
 * Variables *
 *************/
//ZED Subscriber Callbacks
void zed_odom_Callback(const nav_msgs::Odometry::ConstPtr& msg) {
    // Camera position in map frame
    imh_odom_tx = msg->pose.pose.position.x;
    imh_odom_ty = msg->pose.pose.position.y;
    imh_odom_tz = msg->pose.pose.position.z;

    // Orientation quaternion
    imh_odom_qx = msg->pose.pose.orientation.x;
    imh_odom_qy = msg->pose.pose.orientation.y;
    imh_odom_qz = msg->pose.pose.orientation.z;
    imh_odom_qw = msg->pose.pose.orientation.w;
    tf2::Quaternion imh_odom_q(imh_odom_qx, imh_odom_qy, imh_odom_qz, imh_odom_qw);

    // 3x3 Rotation matrix from quaternion
    tf2::Matrix3x3 imh_odom_m(imh_odom_q);

    // Roll Pitch and Yaw from rotation matrix
    imh_odom_m.getRPY(imh_odom_roll, imh_odom_pitch, imh_odom_yaw);
}

void zed_pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    // Camera position in map frame
    imh_pose_tx = msg->pose.position.x;
    imh_pose_ty = msg->pose.position.y;
    imh_pose_tz = msg->pose.position.z;

    // Orientation quaternion
    imh_pose_qx = msg->pose.orientation.x;
    imh_pose_qy = msg->pose.orientation.y;
    imh_pose_qz = msg->pose.orientation.z;
    imh_pose_qw = msg->pose.orientation.w;
    // tf2::Quaternion imh_pose_q(imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw);

    // 3x3 Rotation matrix from quaternion
    // tf2::Matrix3x3 imh_pose_m(imh_pose_q);

    // Roll Pitch and Yaw from rotation matrix
    // imh_pose_m.getRPY(imh_pose_roll, imh_pose_pitch, imh_pose_yaw);

    ROS_INFO("Recieved RAW pose data: [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f]",
        imh_pose_tx, imh_pose_ty, imh_pose_tz,
        imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw);
}

std::tuple<double, double, double, double, double, double, double> get_pose_Handler(){
    // // Create node Handler
    // ros::NodeHandle node_get_Pose;

    // if (algorithm == "zed"){
    //     subscriber_get_Pose = node_get_Pose.subscribe("/zed/pose", 1, zed_pose_Callback);
    //     ROS_INFO("Recieved RAW pose data: [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f]",
    //         imh_pose_tx, imh_pose_ty, imh_pose_tz,
    //         imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw);
    //     ros::spinOnce();
    // }
    // // else if (alogrithm == "other"){
    // // // TODO
    // // }
    // else{
    //     ROS_ERROR("The called pose algortihm is not valid!");
    // }
    ROS_WARN("get_pose_Handler is called! Returning: [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f]",
        imh_pose_tx, imh_pose_ty, imh_pose_tz,
        imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw);
    return std::make_tuple (imh_pose_tx, imh_pose_ty, imh_pose_tz, imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw);
}

bool srv_send_pose(cbf_clf::srv_get_pose::Request &rec, cbf_clf::srv_get_pose::Response &res){
    ROS_INFO("Service call successful.");

    res.x = imh_pose_tx;
    res.y = imh_pose_ty;
    res.z = imh_pose_tz;
    res.qx = imh_pose_qx;
    res.qy = imh_pose_qy;
    res.qz = imh_pose_qz;
    res.qw = imh_pose_qw;

    ROS_INFO("Set response values to: [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f]",
            imh_pose_tx, imh_pose_ty, imh_pose_tz,
            imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw);
    ROS_INFO("Send response: [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f]",
            res.x, res.y, res.z,
            res.qx, res.qy, res.qz, res.qw);

    return true;
}