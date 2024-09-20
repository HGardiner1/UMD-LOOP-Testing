#include <rclcpp/rclcpp.hpp>
#include <can_msgs/msg/frame.hpp>

class CanPublisher : public rclcpp::Node {
public:
    CanPublisher() : Node("can_publisher") {
        publisher_ = this->create_publisher<can_msgs::msg::Frame>("can_tx", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000),
            std::bind(&CanPublisher::timer_callback, this)
        );
    }

private:
    void timer_callback() {
        auto message = can_msgs::msg::Frame();
        message.id = 0x141;  // Example CAN ID
        message.data = {0x01, 0x02, 0x03, 0x04}; // Example data

        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "Published CAN message with ID: %x", message.id);
    }

    rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CanPublisher>());
    rclcpp::shutdown();
    return 0;
}
