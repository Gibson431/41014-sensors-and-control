#include <cmath>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <control_msgs/PointHeadActionGoal.h>

class FetchGaze
{
public:
  FetchGaze()
  {
    // Initialize ROS node handle and subscribers
    nh_.reset(new ros::NodeHandle());

    // Set callback for when marker is recieved
    marker_sub_ =
        nh_->subscribe("/marker_pose", 1, &FetchGaze::markerCallback, this);

    // Initialize the publisher for robot movement
    marker_pub_ = nh_->advertise<control_msgs::PointHeadActionGoal>("/head_controller/point_head/goal", 1);
  }

  void markerCallback(const geometry_msgs::PoseStamped::ConstPtr &pose)
  {
    geometry_msgs::PoseStamped newPose = (*pose);

    control_msgs::PointHeadActionGoal point_head;

    point_head.goal.target.header.stamp = ros::Time::now();
    point_head.goal.target.header.frame_id = "map";
    point_head.goal.target.point.x = newPose.pose.position.x;
    point_head.goal.target.point.y = newPose.pose.position.y;
    point_head.goal.target.point.z = newPose.pose.position.z;
    point_head.goal.min_duration = ros::Duration(1.0);

    marker_pub_.publish(point_head);
  }

private:
  ros::NodeHandlePtr nh_;
  ros::Subscriber marker_sub_;
  ros::Publisher marker_pub_;
};
int main(int argc, char **argv)
{
  ros::init(argc, argv, "fetch_follower_node");
  FetchGaze fetch_follower;

  ros::spin();

  return 0;
}