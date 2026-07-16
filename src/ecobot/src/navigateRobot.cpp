/************************************************************************
BSD 3-Clause License
Copyright (c) 2019, Raj Shinde
Copyright (c) 2019, Prasheel Renkuntla
All rights reserved.
[...license omitted for brevity - unchanged from original...]
*************************************************************************/

/**
 *  @file    navigateRobot.cpp  (adapted for ROS Noetic / TurtleBot3)
 *  @brief   Navigation node - subscribes to cmd_vel
 */

#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/Twist.h>

#include "navigateRobot.hpp"

NavigateRobot::NavigateRobot() {
}

NavigateRobot::~NavigateRobot() {
}

void NavigateRobot::twistRobot(const geometry_msgs::TwistConstPtr &msg) {
  double transVelocity = msg->linear.x;
  double rotVelocity   = msg->angular.z;
  // TurtleBot3 burger: wheel separation=0.160 m, wheel radius=0.033 m
  double velDiff   = (0.160 * rotVelocity) / 2.0;
  double leftPower  = (transVelocity + velDiff) / 0.033;
  double rightPower = (transVelocity - velDiff) / 0.033;
  ROS_INFO_STREAM("\n Left wheel: " << leftPower
                  << ",  Right wheel: " << rightPower << "\n");
}

int NavigateRobot::start(bool flag) {
  ros::NodeHandle nh;
  if (flag) {
    // In Noetic/TurtleBot3 move_base publishes directly to cmd_vel
    ros::Subscriber sub =
        nh.subscribe("cmd_vel", 1000,
        &NavigateRobot::twistRobot, this);
    ros::Rate loop_rate(10);
    while (ros::ok()) {
      ros::spinOnce();
      loop_rate.sleep();
    }
  } else {
    ros::Subscriber sub =
        nh.subscribe("cmd_vel", 5,
        &NavigateRobot::twistRobot, this);
  }
  return 0;
}
