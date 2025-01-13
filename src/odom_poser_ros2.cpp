#include "odom_poser_ros2/odom_poser_ros2.hpp"

namespace odom_poser_ros2
{
    OdomPoserROS2::OdomPoserROS2(const rclcpp::NodeOptions& option): Node("OdomPoserROS2", option)
    {

        sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom",
            rclcpp::SystemDefaultsQoS(),
            std::bind(&OdomPoserROS2::topic_callback, this, _1)
        );

        pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/current", rclcpp::SystemDefaultsQoS());
        pub_path = this->create_publisher<nav_msgs::msg::Path>("/real/path", rclcpp::SystemDefaultsQoS());

        this->declare_parameter("frame_id", "map");
        this->get_parameter("frame_id", frame_id);

        path_.header.frame_id = frame_id;

        RCLCPP_INFO(this->get_logger(), "Start OdomPoserROS2");
    }

    void OdomPoserROS2::topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
    {
        geometry_msgs::msg::PoseStamped p;
        p.header.frame_id = frame_id;
        p.pose = msg->pose.pose;
        path_.poses.push_back(p);

        pub_->publish(p);
        pub_path->publish(path_);
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(odom_poser_ros2::OdomPoserROS2)