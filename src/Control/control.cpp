#include "control.h"

WingIO::WingIO(ros::NodeHandle & control_nh)
        : motor1Topic {"/pan_controller1/command"}
	, motor2Topic {"/pan_controller2/command"}
	, motor3Topic {"/pan_controller3/command"}
	, accelTopic {"/accelerometer"}
{
	 motor1 = control_nh.advertise<std_msgs::Float64>(motor1Topic, 1);
	 motor2 = control_nh.advertise<std_msgs::Float64>(motor2Topic, 1);
	 motor3 = control_nh.advertise<std_msgs::Float64>(motor3Topic, 1);
	 accel = control_nh.subscribe(accelTopic, 1, &WingIO::accelCallback, this);
}

Eigen::Vector3d WingIO::getAcceleration(void){
	Eigen::Vector3d ret;
	accelMutex.lock();
	ret = accelerations;
	accelMutex.unlock();

	return ret;
}

void WingIO::setVelocities(const Eigen::Vector3d & velocities){
	std_msgs::Float64 m1v;
	std_msgs::Float64 m2v;
	std_msgs::Float64 m3v;
	m1v.data = velocities[0];
	m2v.data = velocities[1];
	m3v.data = velocities[2];
	motor1.publish(m1v);
	motor2.publish(m2v);
	motor3.publish(m3v);
}

void WingIO::accelCallback(const std_msgs::Float64MultiArray::ConstPtr& newAccelerations){
	// std::cerr << "Entering Accel Callback" << std::endl;
	accelMutex.lock();
	accelerations[0] = newAccelerations->data[0];
	// std::cerr << newAccelerations->data[0] << std::endl;
	accelerations[1] = newAccelerations->data[1];
	// std::cerr << "" << std::endl;
	accelerations[2] = newAccelerations->data[2];
	// std::cerr << "" << std::endl;
	accelMutex.unlock();
	// std::cerr << "Exiting Accel Callback" << std::endl;
}

