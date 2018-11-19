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

/*************
 * Variables *
 *************/
ros::Publisher pub_pose; // = n.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_attitude/attitude",100);
ros::Publisher pub_throttle; // = n.advertise<std_msgs::Float64>("/mavros/setpoint_attitude/att_throttle", 100);

int pose_msg_count = 1;

/*************
 * Functions *
 *************/
void send_pose_Handler(double x, double y, double z, double qx, double qy, double qz, double qw){
    ros::NodeHandle node_send_Pose;
    pub_pose = node_send_Pose.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_attitude/attitude",100);

    geometry_msgs::PoseStamped cmd_msg_pose;

    cmd_msg_pose.header.stamp = ros::Time::now();
    cmd_msg_pose.header.seq=pose_msg_count;
    cmd_msg_pose.header.frame_id = 1;
    cmd_msg_pose.pose.position.x = x;//0.001*some_object.position_x;
    cmd_msg_pose.pose.position.y = y;//0.001*some_object.position_y;
    cmd_msg_pose.pose.position.z = z;//0.001*some_object.position_z;
    cmd_msg_pose.pose.orientation.x = qx;
    cmd_msg_pose.pose.orientation.y = qy;
    cmd_msg_pose.pose.orientation.z = qz;
    cmd_msg_pose.pose.orientation.w = qw;

    pub_pose.publish(cmd_msg_pose);

    ros::spinOnce();

    ++pose_msg_count;
}

void send_throttle_Handler(double throttle){
    ros::NodeHandle node_send_Throttle;
    pub_throttle = node_send_Throttle.advertise<std_msgs::Float64>("/mavros/setpoint_attitude/att_throttle", 100);

    std_msgs::Float64 cmd_msg_throttle;

    throttle = fmin(1.0, fmax(0.0, throttle));

    cmd_msg_throttle.data = throttle;

    pub_throttle.publish(cmd_msg_throttle);

    ros::spinOnce();
}