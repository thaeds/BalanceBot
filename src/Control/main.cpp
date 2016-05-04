#include <iostream>
#include <eigen3/Eigen/Dense>
#include "control.h"           
#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float64.h>

const int MAX_SPEED = 1023;


int main(int argc, char** argv)
{
	
    ros::init(argc, argv, "control");
    std::cerr << "Control Node Initialized" << std::endl;
    ros::NodeHandle control_nh;
    WingIO wingio(control_nh);

    // Main control loop command loop
    // ros::spin();
    std::cout << "Ros WING enabled use wasd for translation and qe for rotation and i to read accelerometer information." << std::endl;
    char in_command;
    while(1){
	    std::cout << "Golem Wing Waiting For Input" << std::endl;
	    std::cin >> in_command;
	    switch (in_command) {
	    case 'a': {
		    wingio.setVelocities(MAX_SPEED*Eigen::Vector3d(-1,1,1));
		    break;
	    }
	    case 'p': {
		    wingio.setVelocities(MAX_SPEED*Eigen::Vector3d(0,0,0));		    
		    break;
	    }
	    case 'w': {
		    wingio.setVelocities(MAX_SPEED*Eigen::Vector3d(1,1,-1));
		    break;
	    }
	    case 's': {
   		    wingio.setVelocities(MAX_SPEED*Eigen::Vector3d(-1,-1,1));
		    break;
	    }
	    case 'd': {
		    wingio.setVelocities(MAX_SPEED*Eigen::Vector3d(1,-1,-1));	    
		    break;
	    }
	    case 'q': {
		    wingio.setVelocities(MAX_SPEED*Eigen::Vector3d(1,-0.5,1));	    		    
		    break;
	    }
	    case 'e': {
		    wingio.setVelocities(MAX_SPEED*Eigen::Vector3d(-1,0.5,-1));	    		    		    
		    break;
	    }
	    case 'i': {
		    std::cout << "Accelerometer Information Requested" << std::endl;
		    Eigen::Vector3d accelMeasure = wingio.getAcceleration();
		    std::cout << "[X: " << accelMeasure[0] << " Y: " << accelMeasure[1] << " Z: " << accelMeasure[2] << "]Gs" << std::endl;
		    break;
	    }
	    default:
		    std::cout << "Invalid Command" << std::endl;
		    break;
	    }
	    ros::spinOnce();
    }
}
