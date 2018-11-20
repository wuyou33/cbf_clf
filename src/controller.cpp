/*
* Workflow for Controller
* 1) Get pose data
* 2) Get depth map
* 2.1) calculate safe space from depth map
* 3) Define Control Barrier Function (CBF)
* 3.1) Define first derivitave of CBF
* 4) Define Control Lyapunov Function (CLF)
* 4.1) Define first derivitave of CLF
* 5) Define 
* 
* 
*/

#include "cbf_clf/controller.h"

int main(int argc, char** argv){
    //Initizializing a ROS-node called "cbf_clf_controller"
    ros::init(argc, argv, "cbf_clf_controller");
    ros::NodeHandle node;

    ros::Rate loop_rate(loop_rate_); //Needs to be declared AFTER the NodeHandle !

    if(!ros::ok()) ROS_ERROR("ROS not ok! Shutting down!");
    while (ros::ok()){
        // Update pose information
        
        
        ROS_INFO("Service Client Function called");
        cbf_clf::srv_get_pose srv_res;
        client_get_pose = node.serviceClient<cbf_clf::srv_get_pose>("srv_get_pose");
        ROS_INFO("Service Client called");
        pose_tx = srv_res.response.x;
        pose_ty = srv_res.response.y;
        pose_tz = srv_res.response.z;
        pose_qx = srv_res.response.qx;
        pose_qy = srv_res.response.qy;
        pose_qz = srv_res.response.qz;
        pose_qw = srv_res.response.qw;
        ROS_INFO("Recieved: [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f], [%.2f]",
            pose_tx, pose_ty, pose_tz,
            pose_qx, pose_qy, pose_qz, pose_qw);
        tf2::Quaternion pose_q(pose_qx, pose_qy, pose_qz, pose_qw);
        tf2::Matrix3x3 pose_m(pose_q);
        pose_m.getRPY(pose_roll, pose_pitch, pose_yaw);

        ROS_INFO("Pose: x: [%.2f] y: [%.2f] z: [%.2f] - R: [%.2f] P: [%.2f] Y: [%.2f]",
            pose_tx, pose_ty, pose_tz,
            pose_roll * RAD2DEG, pose_pitch * RAD2DEG, pose_yaw * RAD2DEG);

        ros::spinOnce();
        loop_rate.sleep();
    }

return 0;
}