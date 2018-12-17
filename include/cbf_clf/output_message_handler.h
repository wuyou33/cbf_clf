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

#include <mavros_msgs/ActuatorControl.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

#include "cbf_clf/srv_recieve_pose.h"
#include "cbf_clf/srv_recieve_throttle.h"

/*************
 * Variables *
 *************/
ros::Publisher pub_act_control;
ros::Publisher pub_pose_att;
ros::Publisher pub_pose_set;
ros::Publisher pub_throttle;
ros::Subscriber mavros_state_sub;
ros::ServiceServer service_recieve_Pose;
ros::ServiceServer service_recieve_Throttle;
ros::ServiceClient mavros_arming_client;
ros::ServiceClient mavros_set_mode_client;

mavros_msgs::State mavros_current_state;
mavros_msgs::SetMode mavros_offb_set_mode;
mavros_msgs::CommandBool mavros_arm_cmd;

int omh_loop_rate_ = 10;

int act_msg_count = 1;
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
 void send_Actuator_Control_Handler(ros::NodeHandle node_omh, double a0 = 0.0, double a1 = 0.0, double a2 = 0.0, double a3 = 0.0, double a4 = 0.0, double a5 = 0.0, double a6 = 0.0, double a7 = 0.0){
     // Currently we are developing a quadrotor, thus, actuator/motor 4..7 are not used
    pub_act_control = node_omh.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_attitude/attitude", omh_loop_rate_);

    mavros_msgs::ActuatorControl act_control_msg;

    act_control_msg.header.stamp = ros::Time::now();
    act_control_msg.header.seq = act_msg_count;
    act_control_msg.header.frame_id = "1";
    act_control_msg.group_mix = 3;
    act_control_msg.controls[0] = a0;
    act_control_msg.controls[1] = a1;
    act_control_msg.controls[2] = a2;
    act_control_msg.controls[3] = a3;
    act_control_msg.controls[4] = a4;
    act_control_msg.controls[5] = a5;
    act_control_msg.controls[6] = a6;
    act_control_msg.controls[7] = a7;

    pub_act_control.publish(act_control_msg);

    ++act_msg_count;
}

void send_pose_Handler(ros::NodeHandle node_omh, double x, double y, double z, double qx, double qy, double qz, double qw){
    pub_pose_att = node_omh.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_attitude/attitude", omh_loop_rate_);
    pub_pose_set = node_omh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", omh_loop_rate_);

    geometry_msgs::PoseStamped cmd_msg_pose;

    cmd_msg_pose.header.stamp = ros::Time::now();
    cmd_msg_pose.header.seq=pose_msg_count;
    cmd_msg_pose.header.frame_id = "1";
    cmd_msg_pose.pose.position.x = x;
    cmd_msg_pose.pose.position.y = y;
    cmd_msg_pose.pose.position.z = z;
    cmd_msg_pose.pose.orientation.x = qx;
    cmd_msg_pose.pose.orientation.y = qy;
    cmd_msg_pose.pose.orientation.z = qz;
    cmd_msg_pose.pose.orientation.w = qw;

    pub_pose_att.publish(cmd_msg_pose);
    pub_pose_set.publish(cmd_msg_pose);

    ++pose_msg_count;
}

void send_throttle_Handler(ros::NodeHandle node_omh, double throttle){
    pub_throttle = node_omh.advertise<std_msgs::Float64>("/mavros/setpoint_attitude/att_throttle", omh_loop_rate_);

    std_msgs::Float64 cmd_msg_throttle;

    throttle = fmin(1.0, fmax(0.0, throttle));

    cmd_msg_throttle.data = throttle;

    pub_throttle.publish(cmd_msg_throttle);
}

bool srv_recieve_pose(cbf_clf::srv_recieve_pose::Request &req, cbf_clf::srv_recieve_pose::Response &res){
    omh_pose_tx = req.x;
    omh_pose_ty = req.y;
    omh_pose_tz = req.z;
    omh_pose_qx = req.qx;
    omh_pose_qy = req.qy;
    omh_pose_qz = req.qz;
    omh_pose_qw = req.qw;

    res.success = true;

    return true;
}

bool srv_recieve_throttle(cbf_clf::srv_recieve_throttle::Request &req, cbf_clf::srv_recieve_throttle::Response &res){
    omh_throttle = req.throttle;

    res.success = true;

    return true;
}

void get_mavros_state(const mavros_msgs::State::ConstPtr& msg){
    mavros_current_state = *msg;
}