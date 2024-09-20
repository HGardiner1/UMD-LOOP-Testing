cmake_minimum_required(VERSION 3.8)
project(can_example)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(rosidl_default_generators REQUIRED)
find_package(can_msgs REQUIRED)

rosidl_generate_interfaces(can_example
  "msg/YourMessage.msg"  # Adjust according to your message
)

add_executable(can_publisher src/can_publisher.cpp)
add_executable(can_subscriber src/can_subscriber.cpp)

ament_target_dependencies(can_publisher
  rclcpp
  can_msgs
)

ament_target_dependencies(can_subscriber
  rclcpp
  can_msgs
)

install(TARGETS
  can_publisher
  can_subscriber
  DESTINATION lib/can_publisher
)

ament_target_dependencies(your_node_name
  rclcpp
  can_msgs
)
# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
