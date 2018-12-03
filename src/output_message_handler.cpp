#include "cbf_clf/output_message_handler.h"

int main(int argc, char** argv){
    //Initizializing a ROS-node called "cbf_clf_imh"
    ros::init(argc, argv, "cbf_clf_output_message_handler");
    ros::NodeHandle node_omh;

    ros::Rate loop_rate(omh_loop_rate_); //Needs to be declared AFTER the NodeHandle !
    ros::Time mavros_last_request = ros::Time::now();
    mavros_offb_set_mode.request.custom_mode = "OFFBOARD";
    mavros_arm_cmd.request.value = true;

    // Subscribe to current state of MAVROS
    mavros_state_sub = node_omh.subscribe<mavros_msgs::State>("mavros/state", 10, get_mavros_state);

    // Advertise a service which recieves the new pose/throttle data to be send to the Aerocore 2 via MAVROS/MAVLink
    service_recieve_Pose = node_omh.advertiseService("srv_recieve_pose", srv_recieve_pose);
    service_recieve_Throttle = node_omh.advertiseService("srv_recieve_throttle", srv_recieve_throttle);

    // Subscribe to a Service to recieve Amring and Set Moe from MAVROS
    mavros_arming_client = node_omh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    mavros_set_mode_client = node_omh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    // wait for FCU connection
    while(ros::ok() && !mavros_current_state.connected){
        ros::spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("FCU connection established");

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        // Publish Pose Data to MAVROS/MAVLink
        send_pose_Handler(node_omh, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
        send_throttle_Handler(node_omh, 0.3); // Idle throttle
        ros::spinOnce();
        loop_rate.sleep();
    }

    /*******************
     * Main while-loop *
     *******************/
    while(ros::ok()){
        if(mavros_current_state.mode != "OFFBOARD" && (ros::Time::now() - mavros_last_request > ros::Duration(5.0))){
            mavros_set_mode_client.call(mavros_offb_set_mode);
            if(mavros_offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard enabled");
            }
            mavros_last_request = ros::Time::now();
        }
        else{
            if(!mavros_current_state.armed &&(ros::Time::now() - mavros_last_request > ros::Duration(5.0))){
                mavros_arming_client.call(mavros_arm_cmd);
                if(mavros_arm_cmd.response.success){
                    ROS_INFO("Vehicle armed");
                }
                mavros_last_request = ros::Time::now();
            }
        }

        // Publish Pose Data to MAVROS/MAVLink
        send_pose_Handler(node_omh, omh_pose_tx, omh_pose_ty, omh_pose_tz, omh_pose_qx, omh_pose_qy, omh_pose_qz, omh_pose_qw);
        send_throttle_Handler(node_omh, omh_throttle);

        ros::spinOnce();
        loop_rate.sleep();
    }

return 0;
}