#include <actionlib/client/simple_action_client.h>
#include <chrono>
#include <cmath>
#include <control_msgs/PointHeadAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <mutex>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <thread>

class FetchGaze {
public:
  FetchGaze() : ac_("head_controller/point_head", true) {
    // Initialize ROS node handle and subscribers
    nh_.reset(new ros::NodeHandle());

    // Set callback for when marker is recieved
    marker_sub_ =
        nh_->subscribe("/marker_pose", 1, &FetchGaze::markerCallback, this);

    // Initialize the publisher for robot movement
    // marker_pub_ = nh_->advertise<control_msgs::PointHeadActionGoal>(
    //     "/head_controller/point_head/goal", 1);

    // ac_("head_controller/point_head", true);

    ROS_INFO("Waiting for gaze server to start.");
    ac_.waitForServer();
    ROS_INFO("Gaze server started.");
  }

  void markerCallback(const geometry_msgs::PoseStamped::ConstPtr &pose) {
    geometry_msgs::PoseStamped newPose = (*pose);
    {
      std::unique_lock<std::mutex> lck(mtx_);
      current_goal_ = newPose.pose;
      has_goal_ = true;
    }
    // marker_pub_.publish(point_head);
  }

  void gazeThread(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    while (ros::ok()) {
      if (has_goal_) {
        control_msgs::PointHeadGoal point_head;

        // point_head.goal.target.header.stamp = ros::Time::now();
        point_head.target.header.frame_id = "map";
        point_head.min_duration = ros::Duration(0.5);
        point_head.max_velocity = 360;
        {
          std::unique_lock<std::mutex> lck(mtx_);
          point_head.target.point.x = current_goal_.position.x;
          point_head.target.point.y = current_goal_.position.y;
          point_head.target.point.z = current_goal_.position.z;
        }

        ac_.sendGoal(point_head);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }

private:
  ros::NodeHandlePtr nh_;
  ros::Subscriber marker_sub_;
  ros::Publisher marker_pub_;

  std::thread head_thread_;

  bool has_goal_ = false;
  geometry_msgs::Pose current_goal_;
  std::mutex mtx_;
  actionlib::SimpleActionClient<control_msgs::PointHeadAction> ac_;
};
int main(int argc, char **argv) {
  ros::init(argc, argv, "fetch_gaze_node");
  FetchGaze fetch_gaze;
  std::thread head_thread(&FetchGaze::gazeThread, &fetch_gaze);

  ros::spin();

  return 0;
}
