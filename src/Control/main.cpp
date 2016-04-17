#include <iostream>
#include "control.h"
#include <ros/ros.h>

using namespace std;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "control");
    cerr << "Control Node Initialized" << endl;
    ros::NodeHandle control_nh;
    ros::spin();
}
