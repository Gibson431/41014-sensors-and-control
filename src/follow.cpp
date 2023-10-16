#include <cmath>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

class FetchFollower {
public:
  FetchFollower() {
    // Initialize ROS node handle and subscribers
    nh_.reset(new ros::NodeHandle());

    // Set callback for when marker is recieved
    marker_sub_ =
        nh_->subscribe("/marker_pose", 1, &FetchFollower::markerCallback, this);

    // Initialize the publisher for robot movement
    marker_pub_ = nh_->advertise<geometry_msgs::PoseStamped>("/waypoint", 1);
  }

  void markerCallback(const geometry_msgs::PoseStamped::ConstPtr &pose) {
    geometry_msgs::PoseStamped newPose = (*pose);

    tf2::Quaternion input_quat, rotation_quat, result_quat;
    tf2::fromMsg(newPose.pose.orientation, input_quat);

    // rotation_quat.setRPY(0.0, -M_PI / 2, 0.0);
    // result_quat = input_quat * rotation_quat;

    rotation_quat.setRPY(-M_PI / 2, 0.0, 0.0);
    result_quat = input_quat * rotation_quat;

    rotation_quat.setRPY(0.0, 0.0, M_PI / 2);
    result_quat = result_quat * rotation_quat;

    newPose.pose.orientation = tf2::toMsg(result_quat);

    double r, p, y;

    tf2::getEulerYPR(result_quat, y, p, r);
    // newPose.pose.position.x -= 2 * cos(result_quat.getZ());
    // newPose.pose.position.y -= 2 * sin(result_quat.getZ());
    newPose.pose.position.x -= 2 * cos(y);
    newPose.pose.position.y -= 2 * sin(y);

    marker_pub_.publish(newPose);
  }

private:
  ros::NodeHandlePtr nh_;
  ros::Subscriber marker_sub_;
  ros::Publisher marker_pub_;
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "fetch_follower_node");
  FetchFollower fetch_follower;

  ros::spin();

  return 0;
}
