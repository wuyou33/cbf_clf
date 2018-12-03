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
#include "std_msgs/Float64.h"

#include "ros/ros.h"

#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Vector3Stamped.h"

#include "nav_msgs/Odometry.h"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

#include "cbf_clf/srv_recieve_pose.h"
#include "cbf_clf/srv_recieve_throttle.h"

/*************
 * Variables *
 *************/
ros::Publisher pub_pose;
ros::Publisher pub_throttle;
ros::ServiceServer service_recieve_Pose;
ros::ServiceServer service_recieve_Throttle;

int omh_loop_rate_ = 60;

int pose_msg_count = 1;

// Pose Information
double omh_pose_tx, omh_pose_ty, omh_pose_tz;
double omh_pose_qx, omh_pose_qy, omh_pose_qz, omh_pose_qw;

// Thurst Information
double omh_thrust;
double omh_throttle;

/*************
 * Functions *
 *************/
void send_pose_Handler(ros::NodeHandle node_omh, double x, double y, double z, double qx, double qy, double qz, double qw){
    pub_pose = node_omh.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_attitude/attitude",100);

    geometry_msgs::PoseStamped cmd_msg_pose;

    cmd_msg_pose.header.stamp = ros::Time::now();
    cmd_msg_pose.header.seq=pose_msg_count;
    cmd_msg_pose.header.frame_id = 1;
    cmd_msg_pose.pose.position.x = x;
    cmd_msg_pose.pose.position.y = y;
    cmd_msg_pose.pose.position.z = z;
    cmd_msg_pose.pose.orientation.x = qx;
    cmd_msg_pose.pose.orientation.y = qy;
    cmd_msg_pose.pose.orientation.z = qz;
    cmd_msg_pose.pose.orientation.w = qw;

    pub_pose.publish(cmd_msg_pose);
    ROS_INFO("Publishing /mavros/setpoint_attitude/attitude - [%.2f, %.2f, %.2f], [%.2f, %.2f, %.2f, %.2f]", x, y, z, qx, qy, qz, qw);

    ++pose_msg_count;
}

void send_throttle_Handler(ros::NodeHandle node_omh, double throttle){
    pub_throttle = node_omh.advertise<std_msgs::Float64>("/mavros/setpoint_attitude/att_throttle", 100);

    std_msgs::Float64 cmd_msg_throttle;

    throttle = fmin(1.0, fmax(0.0, throttle));

    cmd_msg_throttle.data = throttle;

    pub_throttle.publish(cmd_msg_throttle);
    ROS_INFO("Publishing /mavros/setpoint_attitude/att_throttle - [%.2f]", throttle);
}

bool srv_recieve_pose(cbf_clf::srv_recieve_pose::Request &req, cbf_clf::srv_recieve_pose::Response &res){
    omh_pose_tx = req.x;
    omh_pose_ty = req.y;
    omh_pose_tz = req.z;
    omh_pose_qx = req.qx;
    omh_pose_qy = req.qy;
    omh_pose_qz = req.qz;
    omh_pose_qw = req.qw;
    
    res.success = (bool)true;

    return true;
}

bool srv_recieve_throttle(cbf_clf::srv_recieve_throttle::Request &req, cbf_clf::srv_recieve_throttle::Response &res){
    omh_throttle = req.throttle;

    res.success = (bool)true;

    return true;
}