// Copyright 2019 FZI Forschungszentrum Informatik, Created on behalf of Universal Robots A/S
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Felix Exner exner@fzi.de
 * \date    2019-06-12
 *
 * \author  Mads Holm Peters
 * \date    2022-02-25
 *
 */
//----------------------------------------------------------------------

#include "rclcpp/rclcpp.hpp"
#include "ur_robot_driver/controller_stopper.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("controller_stopper_node");

  bool headless_mode = node->declare_parameter<bool>("headless_mode", false);
  node->get_parameter<bool>("headless_mode", headless_mode);
  bool joint_controller_active = node->declare_parameter<bool>("joint_controller_active", true);
  node->get_parameter<bool>("joint_controller_active", joint_controller_active);

  // If headless mode is not active, but the joint controllers are we should stop the joint controllers during startup
  // of the node
  bool stop_controllers_on_startup = false;
  if (joint_controller_active == true && headless_mode == false) {
    stop_controllers_on_startup = true;
  }

  ControllerStopper stopper(node, stop_controllers_on_startup);

  rclcpp::spin(node);

  return 0;
}
