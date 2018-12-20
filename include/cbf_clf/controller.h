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

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

// Custom Header Files
#include "cbf_clf/input_message_handler.h"
#include "cbf_clf/output_message_handler.h"

/*************
 * Variables *
 *************/
ros::Subscriber zedPose;
ros::ServiceClient client_get_pose;
ros::ServiceClient client_recieve_pose;
ros::ServiceClient client_recieve_throttle;
int loop_rate_ = 10; //Loop Rate of 10 Hz

std::string flight_trajectory;
// std::string control_mode;

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
    srv_res.request.dummy = 0.0;

    client_get_pose = node.serviceClient<cbf_clf::srv_get_pose>("srv_get_pose");
    client_get_pose.call(srv_res);

    pose_tx = srv_res.response.x;
    pose_ty = srv_res.response.y;
    pose_tz = srv_res.response.z;
    pose_qx = srv_res.response.qx;
    pose_qy = srv_res.response.qy;
    pose_qz = srv_res.response.qz;
    pose_qw = srv_res.response.qw;

    tf2::Quaternion pose_q(pose_qx, pose_qy, pose_qz, pose_qw);
    tf2::Matrix3x3 pose_m(pose_q);
    
    pose_m.getRPY(pose_roll, pose_pitch, pose_yaw);
}

void send_pose(ros::NodeHandle node, double x = 0.0, double y = 0.0, double z = 1.0, double qx = 0.0, double qy = 0.0, double qz = 0.0, double qw = 1.0){
    cbf_clf::srv_recieve_pose srv_res;
    srv_res.request.x = x;
    srv_res.request.y = y;
    srv_res.request.z = z;
    srv_res.request.qx = qx;
    srv_res.request.qy = qy;
    srv_res.request.qz = qz;
    srv_res.request.qw = qw;

    client_recieve_pose = node.serviceClient<cbf_clf::srv_recieve_pose>("srv_recieve_pose");
    client_recieve_pose.call(srv_res);

    bool status = (bool)srv_res.response.success;
    if(!status){
        ROS_WARN("Couldn't send calculated pose data!");
    }
}

void send_throttle(ros::NodeHandle node, double throttle = 0.5){
    cbf_clf::srv_recieve_throttle srv_res;
    srv_res.request.throttle = throttle;

    client_recieve_throttle = node.serviceClient<cbf_clf::srv_recieve_throttle>("srv_recieve_throttle");
    client_recieve_throttle.call(srv_res);

    bool status = (bool)srv_res.response.success;
    if(!status){
        ROS_WARN("Couldn't send calculated throttle!");
    }
}

void send_trajectory(ros::NodeHandle node, ros::Time start_time = ros::Time::now(), std::string traj_name = "const_height"){
    ros::Time current_time = ros::Time::now();
    double looptime = 30; // s
    double progress = std::fmod((current_time.toSec() - start_time.toSec()), looptime);

    double x = 0.0;
    double y = 0.0;
    double z = 1.0;
    double qx = 0.0;
    double qy = 0.0;
    double qz = 0.0;
    double qw = 1.0;
    double pi = 3.1415927;
    double angle = 2.0*pi*progress;
    tf2::Quaternion q;

    if ("const_height"==traj_name){
        x = 0.0;
        y = 0.0;
        z = 1.0;
        qx = 0.0;
        qy = 0.0;
        qz = 0.0;
        qw = 1.0;
    }
    else if("circle"==traj_name){
        x = cos(angle) - 1.0;
        y = sin(angle);
        z = 1.0;
        double roll = 0.0;
        double pitch = 0.0;
        double yaw = angle;
        q.setRPY(roll, pitch, yaw);
        q.normalize();
        qx = q.x();
        qy = q.y();
        qz = q.z();
        qw = q.w();
    }
    else{ // Again const height, just in case as a backup.
        x = 0.0;
        y = 0.0;
        z = 1.0;
        qx = 0.0;
        qy = 0.0;
        qz = 0.0;
        qw = 1.0;
    }
    send_pose(node, x, y, z, qx, qy, qz, qw);
}