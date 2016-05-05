#pragma once

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Float64MultiArray.h>
#include <string>
#include <mutex>
#include <tf/tf.h>

class WingIO {
    private:
    const std::string motor1Topic;
    const std::string motor2Topic;
    const std::string motor3Topic;
    const std::string gyroTopic;
    const std::string gainsTopic;
    ros::Subscriber gains;
    ros::Subscriber gyro;
    ros::Publisher motor1;
    ros::Publisher motor2;
    ros::Publisher motor3;
    Eigen::Vector3d accelerations;
    std::mutex accelMutex;
    float kP = 1;
    float kI = 0;
    float kD = 0;
    float currentAngle = 0;
    float commandAngle = -0.418;
    float currentCommand = 0;

public:
    WingIO(ros::NodeHandle &nh);
    void setVelocities(const Eigen::Vector3d & velocieties);
    Eigen::Vector3d getAcceleration(void);
    void accelCallback(const std_msgs::Float64MultiArray::ConstPtr &newAccelerations);
    void gyroCallback(const sensor_msgs::Imu::ConstPtr& msg);
    void PIDCallback(const std_msgs::Float64MultiArray::ConstPtr &newPIDs);
};
