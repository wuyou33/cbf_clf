/************
 * Includes *
 ************/
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"

// Custom Header Files
//#include "input_message_handler.h"
#include "../include/cbf_clf/input_message_handler.h"

/*************
 * Variables *
 *************/
ros::Subscriber zedPose;
int loop_rate_ = 10; //Loop Rate of 10 Hz

/*************
 * Functions *
 *************/