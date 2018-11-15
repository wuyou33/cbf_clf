/************
 * Includes *
 ************/
// Standard Header Files
#include <iostream>
#include <stdio.h>
#include <string>
#include <array>
#include <cmath>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

#include <boost/thread/thread.hpp>

// Custom Header Files
#include "input_message_handler.h"

/*************
 * Variables *
 *************/
ros::Subscriber pose;
int loop_rate_ = 10; //Loop Rate of 10 Hz
std::string pose_algorithm = "zed";

/*************
 * Functions *
 *************/