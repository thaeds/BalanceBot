#pragma once

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <string>
#include <mutex>

class WingIO {
    private:
    const std::string motor1Topic;
    const std::string motor2Topic;
    const std::string motor3Topic;
    const std::string accelTopic;
    ros::Subscriber accel;
    ros::Publisher motor1;
    ros::Publisher motor2;
    ros::Publisher motor3;
    Eigen::Vector3d accelerations;
    std::mutex accelMutex;

public:
    WingIO(ros::NodeHandle &nh);
    void setVelocities(const Eigen::Vector3d & velocieties);
    Eigen::Vector3d getAcceleration(void);
    void accelCallback(const std_msgs::Float64MultiArray::ConstPtr &newAccelerations);
};
