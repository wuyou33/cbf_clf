#include "cbf_clf/output_message_handler.h"

int main(int argc, char** argv){
    //Initizializing a ROS-node called "cbf_clf_imh"
    ros::init(argc, argv, "cbf_clf_output_message_handler");
    ros::NodeHandle node_omh;

    ros::Rate loop_rate(omh_loop_rate_); //Needs to be declared AFTER the NodeHandle !

    // Publish Pose Data to MAVROS/MAVLink

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

    send_pose_Handler(node_omh, omh_pose_tx, omh_pose_ty, omh_pose_tz, omh_pose_qx, omh_pose_qy, omh_pose_qz, omh_pose_qw);
    send_throttle_Handler(node_omh, omh_throttle);

    // Advertise a service which recieves the new pose/throttle data to be send to the Aerocore 2 via MAVROS/MAVLink
    service_recieve_Pose = node_omh.advertiseService("srv_recieve_pose", srv_recieve_pose);
    service_recieve_Throttle = node_omh.advertiseService("srv_recieve_throttle", srv_recieve_throttle);

    ros::spin();
    loop_rate.sleep();

return 0;
}