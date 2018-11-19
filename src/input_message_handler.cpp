#include "../include/cbf_clf/input_message_handler.h"

int main(int argc, char** argv){
    //Initizializing a ROS-node called "cbf_clf_imh"
    ros::init(argc, argv, "cbf_clf_input_message_handler");
    ros::NodeHandle node_imh;

    ros::Rate loop_rate(imh_loop_rate_); //Needs to be declared AFTER the NodeHandle !

    if (pose_algorithm == "zed"){
        subscriber_get_Pose = node_imh.subscribe("/zed/pose", 1, zed_pose_Callback);
        ROS_INFO("Recieved RAW pose data: [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f]",
            imh_pose_tx, imh_pose_ty, imh_pose_tz,
            imh_pose_qx, imh_pose_qy, imh_pose_qz, imh_pose_qw);
    }
    // else if (alogrithm == "other"){
    // // TODO
    // }
    else{
        ROS_ERROR("The called pose algortihm is not valid!");
    }

    ros::spin();
    loop_rate.sleep();


return 0;
}