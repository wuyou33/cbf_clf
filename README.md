# CBF-CLF (Control-Barrier-Function-Control-Control-Lyapunov-Function)

## General
This repository is an open-source implementation of the control laws discussed in [1](http://hybrid-robotics.berkeley.edu/ACC2016_Safety_Control_Planar_Quadrotor.html "Wu, Sreenath 2016 - Safety-critical control of a planar") and [2](http://hybrid-robotics.berkeley.edu/DSCC2016_Safety_Control_3D_Quadrotor.html "Wu, Sreenath 2016 - Safety-Critical Control of a 3D"). It is written in C++ for ROS and optimized to work on the [Jetson TX2](https://www.nvidia.com/en-us/autonomous-machines/embedded-systems-dev-kits-modules/ "Jetson TX2") and the [Aerocore 2 for Jetson TX2](https://store.gumstix.com/development-boards/aerocore-2/aerocore2-for-nvidia-jetson.html "Aerocore 2"). As for the onboard camera, a [ZED Mini](https://www.stereolabs.com/zed-mini/ "ZED Mini") was used.

## License
The project is an open-source project based on the 3-Clause BSD License.

## Dependencies
The code dependce on the following packages:
* [ROS Kinetic](http://wiki.ros.org/kinetic "ROS Kinetic")
* [ZED SDK v2.7 for Jetson TX2](https://www.stereolabs.com/developers/release/ "ZED SDK") and the [ZED ROS Wrapper](https://github.com/stereolabs/zed-ros-wrapper "ZED ROS Warpper on GitHub")
* [MAVROS](http://wiki.ros.org/mavros "MAVROS")

## Installation
### Prerequisites
* The Jetson TX2 flashed to L4T 28.2.1 (via [JetPack 3.3](https://developer.nvidia.com/embedded/downloads#?search=jetpack "JetPack 3.3") with CUDA 9).
* The Aerocore 2 with a [flashed Bootloader](https://www.gumstix.com/images/aerocore_2_user_manual.pdf "Aerocore 2 User Manual with Installtion Guide") and a flashed Firmware either via [QGroundControl](http://qgroundcontrol.com/ "QGroundControl") or via [Building your own Firmware](https://www.gumstix.com/images/aerocore_2_user_manual.pdf "Aerocore 2 User Manual with Installtion Guide"). _Note: It may be neccessary to reflash the Firmware later on, but the part is still under development._
* A computer running Ubuntu 16.04 LTS.
### Flashing the correct Device Tree on the Jetson
As the Aerocore 2's USB port don't natively work with the Jetson, you'll have to flash it using the correct .dts-file [provided by gumstix.com](https://geppetto.gumstix.com/#!/gumstix/preview/3062 "Download BSP"). To do so, [download the BSP zip file](https://geppetto.gumstix.com/#!/gumstix/preview/3062 "Download BSP") to a computer running a native Ubuntu 16.04. _Note: while a lot of people got the JetPack 3.3 to work inside a virtual machine, we recommend using a native installation._ Afterwards follow the instructions provided in the Readme-file.
### Installing ROS
As MAVROS will require ```catkin build``` instead of the commonly used ```catkin_make```, the installtion via the current [Installation Guide](http://wiki.ros.org/kinetic/Installation "ROS Kinetic Installtion Guide") is not possible, without further modifications. Nevertheless, the following steps are indeed based on the [Installation Guide](http://wiki.ros.org/kinetic/Installation "ROS Kinetic Installtion Guide"). Thus, for further information we recommend the aforementioned guide.
#### Step 1 - Setting up the ```sources.list``` and the keys
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
```
#### Step 2 - Installation
While we recommend using the full desktop installer, a different installer may be more suitable for you. In that case, please refer to the official [Installation Guide](http://wiki.ros.org/kinetic/Installation "ROS Kinetic Installtion Guide"). _Note: this may have an effect later, which will __not__ be covered by this installation guide!_
Otherwise, we will assume, that the full desktop version of ROS kinetic is installed.
```
sudo apt-get install ros-kinetic-desktop-full
```
#### Step 3 - Install ```rosdep```
```
sudo rosdep init && rosdep update
```
#### Step 4 - Enviroment setup
```
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc && source ~/.bashrc
```
#### Step 5 - Building dependencies
Up until now, we strictly followed the official [Installation Guide](http://wiki.ros.org/kinetic/Installation "ROS Kinetic Installtion Guide"). But the next command is different, notice the additional ```python-catkin-tools``` in the following command.
```
sudo apt-get install python-rosinstall python-catkin-tools python-rosinstall-generator python-wstool build-essential -y
```
#### Step 6 - Creating the ROS Workspace
```
mkdir -p ~\catkin_ws\src
cd ~/catkin_ws
```
From now on, __do not follow the official guide anymore!__
```
catkin init
catkin config
catkin build
```
### Installing the ZED SDK and the ZED ROS Wrapper
#### Step 1 - Installing the ZED SDK
In general, the [Installation Guide can be found here](https://www.stereolabs.com/docs/getting-started/installation/ "ZED SDK Installation Guide"), the corresponding [Downloads here](https://www.stereolabs.com/developers/release/ "Download ZED SDK"). While the this guide only covers the installation for the Jetson TX2, the steps are pretty much the same, just download the correct version of the ZED SDK. Be advised, that we are working with __CUDA 9__, thus, the support for CUDA 10 is not guaranteed.
For the Jetson TX2:
```
cd ~/ && wget https://download.stereolabs.com/zedsdk/2.7/tegrax2 && chmod +x ZED_SDK_Linux_*.run
```
For a computer running Ubuntu 16.04 LTS:
```
cd ~/ && wget https://download.stereolabs.com/zedsdk/2.7/ubuntu16_cuda9 && chmod +x ZED_SDK_Linux_*.run
```
Afterwards, to start the ZED SDK use:
```
./ZED_SDK_Linux_*.run
```
As we are going to install the ZED ROS wrapper, starting the ZED SDK is no longer needed.
#### Step 2 - Installing the ZED ROS Wrapper
The following guide is based on the corresponding [GitHub Repository for the ZED ROS Wrapper](https://github.com/stereolabs/zed-ros-wrapper "ZED ROS Wrapper on GitHub"). Again, we need to modify it installation process to utilize ```catkin build``` instead of ```catkin_make```.
```
cd ~/catkin_ws/src
git clone https://github.com/stereolabs/zed-ros-wrapper.git
cd ../
catkin build
echo "source ./devel/setup.bash" >> ~/.bashrc && source ~/.bashrc
```
#### Step 3 - Verification
To verify the installation of the ZED SDK and the ZED ROS Wrapper, we suggest you run one of the following commands to see if you get any data (video feed, pose/odom, IMU, ...).
For the ZED Mini:
```
roslaunch zed_display_rviz display_zedm.launch
```
For the ZED (which is __not__ supported by this guide, for it does __not__ have an onboard IMU):
```
roslaunch zed_display_rviz display.launch
```
### Installing MAVROS
To communicate with the [Aerocore 2](https://store.gumstix.com/development-boards/aerocore-2/aerocore2-for-nvidia-jetson.html "Aerocore 2") [MAVROS](http://wiki.ros.org/mavros "MAVROS") is needed. It can be installed either via a Binary Installation or via a Source Installation, for both the [Installation Guide](https://dev.px4.io/en/ros/mavros_installation.html "MAVROS Installation Guide") can be found online. Currently, this guide is using the installation from source.
#### Step 1 - Verify your ROS installation
```
cd ~/catkin_ws
catkin init
wstool init src
```
#### Step 2 - Initialize your Workspace for use with ```wstool```
```
wstool init ~/catkin_ws/src
```
#### Step 3 - Installing MAVLink
```
rosinstall_generator --rosdistro kinetic mavlink | tee /tmp/mavros.rosinstall
```
#### Step 4 - Installing MAVROS
While the [Installation Guide](https://dev.px4.io/en/ros/mavros_installation.html "MAVROS Installation Guide") lets you choose between a "Released/stable" version and a "Latest source" version, we recommend using the stable version of MAVROS and will assume you do too.
```
rosinstall_generator --upstream mavros | tee -a /tmp/mavros.rosinstall
```
#### Step 5 - Creating the workspace & isntalling the dependencies
```
wstool merge -t src /tmp/mavros.rosinstall
wstool update -t src -j4
rosdep install --from-paths src --ignore-src -y
```
#### Step 6 - Installing GeographicLib datasets:
```
sudo chmod +x ./src/mavros/mavros/scripts/install_geographiclib_datasets.sh
sudo ./src/mavros/mavros/scripts/install_geographiclib_datasets.sh
```
#### Step 7 - Building the source
```
catkin build
```
#### Step 8 - Adding MAVROS to your source
```
echo "source devel/setup.bash" >> ~/.bashrc && source ~/.bashrc
```
### Installing cbf-clf
Currently, only installation from source is supported.
```
cd ~/catkin_ws/src
git clone https://github.com/JohannLange/cbf_clf.git
```
In general we would recommend building from the stable-branch, but as the code is still under development, there might not be a stable version. In that case, please choose the development-branch.
```
cd cbf_clf
git checkout stable
```
Continuing the installation
```
cd ~/catkin_ws
catkin build
```
