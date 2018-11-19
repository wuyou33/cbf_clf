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

#include "../include/cbf_clf/controller.h"

int main(int argc, char** argv){
    //Initizializing a ROS-node called "cbf_clf_controller"
    ros::init(argc, argv, "cbf_clf_controller");
    ros::NodeHandle node;

    ros::Rate loop_rate(loop_rate_); //Needs to be declared AFTER the NodeHandle !

    if(!ros::ok()) ROS_ERROR("ROS not ok! Shutting down!");
    while (ros::ok()){
        // Update pose information
        get_pose();
        ROS_INFO("Pose: x: [%.2f] y: [%.2f] z: [%.2f] - R: [%.2f] P: [%.2f] Y: [%.2f]",
            pose_tx, pose_ty, pose_tz,
            pose_roll * RAD2DEG, pose_pitch * RAD2DEG, pose_yaw * RAD2DEG);

        ros::spinOnce();
        loop_rate.sleep();
    }

return 0;
}