#include "cbf_clf/input_message_handler.h"

int main(int argc, char** argv){
    //Initizializing a ROS-node called "cbf_clf_imh"
    ros::init(argc, argv, "cbf_clf_input_message_handler");
    ros::NodeHandle node_imh;

    ros::Rate loop_rate(imh_loop_rate_); //Needs to be declared AFTER the NodeHandle !

    node_imh.getParam("/pose_algorithm", pose_algorithm);

    if (pose_algorithm == "zed"){
        subscriber_get_Pose = node_imh.subscribe("/zed/pose", imh_loop_rate_, pose_Callback);
    }
    else if (pose_algorithm == "mocap"){
        subscriber_get_Pose = node_imh.subscribe("/qrotor1/pose", imh_loop_rate_, pose_Callback);
    }
    else{
        ROS_WARN("The called pose algortihm is not valid! Assuming default (zed)");
        subscriber_get_Pose = node_imh.subscribe("/zed/pose", imh_loop_rate_, pose_Callback);
    }

    service_send_Pose = node_imh.advertiseService("srv_get_pose", srv_send_pose);

    ros::spin();
    loop_rate.sleep();

return 0;
}