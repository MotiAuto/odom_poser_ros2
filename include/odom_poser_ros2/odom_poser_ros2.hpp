#ifndef ODOM_POSER_ROS2_HPP_
#define ODOM_POSER_ROS2_HPP_

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <string>

using std::placeholders::_1;

namespace odom_poser_ros2
{
    class OdomPoserROS2 : public rclcpp::Node
    {
        public:
        explicit OdomPoserROS2(const rclcpp::NodeOptions& option = rclcpp::NodeOptions());

        void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg);

        private:
        rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_;
        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_;
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_path;
        std::string frame_id;
        nav_msgs::msg::Path path_;
    };
}

#endif