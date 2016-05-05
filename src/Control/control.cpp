#include "control.h"
#include <chrono>
#include <cmath>

WingIO::WingIO(ros::NodeHandle & control_nh)
        : motor1Topic {"/pan_controller1/command"}
	, motor2Topic {"/pan_controller2/command"}
	, motor3Topic {"/pan_controller3/command"}
	, gyroTopic {"/imu"}
    , gainsTopic{"/gains"}
{
	 motor1 = control_nh.advertise<std_msgs::Float64>(motor1Topic, 1);
	 motor2 = control_nh.advertise<std_msgs::Float64>(motor2Topic, 1);
	 motor3 = control_nh.advertise<std_msgs::Float64>(motor3Topic, 1);
	 gyro = control_nh.subscribe(gyroTopic, 1, &WingIO::gyroCallback, this);
	 gains = control_nh.subscribe(gainsTopic, 100, &WingIO::PIDCallback, this);
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
	m1v.data = -velocities[0];
	m2v.data = -velocities[1];
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

int rad2deg(float rad) {
    return (int) ( rad * 180 ) / M_PI;
}

void WingIO::gyroCallback(const sensor_msgs::Imu::ConstPtr& msg) {
	static double P = 0;
	static double I = 0;
	static double D = 0;
	static double prvError = 0;
	static std::chrono::time_point<std::chrono::high_resolution_clock> prvTime = std::chrono::high_resolution_clock::now();

	tf::Quaternion q;
	double roll, pitch, yaw;
	tf::quaternionMsgToTF(msg->orientation, q);
	tf::Matrix3x3(q).getRPY(roll, pitch, yaw);

	//std::cerr << "RPY = " << roll << ", " << pitch << ", " << yaw << std::endl;
	//std::cerr << "Pitch = " << pitch << std::endl;

	currentAngle = pitch;

	std::chrono::time_point<std::chrono::high_resolution_clock> curTime = std::chrono::high_resolution_clock::now();
	double durSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - prvTime).count();
	double curError = currentAngle - commandAngle;
	std::cerr << "Command " << currentCommand << " Angle Error: " << curError << ", currAngle:commaAngle (" << currentAngle << ":" << commandAngle << "" << std::endl;
	P = kP * curError;
	I += kI * curError * durSeconds;
	D = kD * (curError - prvError) / durSeconds;
	P = abs(curError) > 0.3 ? 2 * P : P;
	std::cerr << "P: "<< P << " I: "<< I << " D: "<< D << std::endl;	
	currentCommand = - (P + I + D);

	
	setVelocities(Eigen::Vector3d(currentCommand, currentCommand, currentCommand));

	prvTime = curTime;
	prvError = curError;
}

void WingIO::PIDCallback(const std_msgs::Float64MultiArray::ConstPtr &newPIDs){
	kP = newPIDs->data[0];
	kI = newPIDs->data[1];
	kD = newPIDs->data[2];
	commandAngle = newPIDs->data[3];
}
