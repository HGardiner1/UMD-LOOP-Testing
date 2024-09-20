#include <rclcpp/rclcpp.hpp>
#include <can_msgs/msg/frame.hpp>

class CanSubscriber : public rclcpp::Node {
public:
    CanSubscriber() : Node("can_subscriber") {
        subscription_ = this->create_subscription<can_msgs::msg::Frame>(
            "can_rx", 10,
            std::bind(&CanSubscriber::topic_callback, this, std::placeholders::_1)
        );
    }

private:
    void topic_callback(const can_msgs::msg::Frame::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received CAN message with ID: %x", msg->id);
    }

    rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CanSubscriber>());
    rclcpp::shutdown();
    return 0;
}
