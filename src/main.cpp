#include "robot.h"
#include "common_utils.h"
#include "io_utils.h"
#include "actions.h"

#include <Arduino.h>

#include <unordered_map>
#include <string>
#include <variant>

struct Config
{
  int serial_baud = 9600;
  Ms delay_after_io_init{2000};
  io_utils::LogLevel log_level = io_utils::LogLevel::DEBUG;

  std::unordered_map<std::string, Action> actions = {
      {"f", ActionType::GoForward{}},
      {"b", ActionType::GoBackward{}},
      {"l", ActionType::TurnLeft{}},
      {"r", ActionType::TurnRight{}},
      {"bf", ActionType::BackAndForth{}},
      {"s", ActionType::Square{}},
      {"x", ActionType::X{}},
      {"c", ActionType::Custom{}},
  };

  RobotSettings robot_settings = {
      .left_wheel_settings = {
          .control_pin = Pin{5},
          .feedback_pin = Pin{6},
          .speed_dead_range = Speed{4},
          .circumference = Meter{0.205},
          .label = "right-wheel",
      },
      .right_wheel_settings = {
          .control_pin = Pin{7},
          .feedback_pin = Pin{8},
          .speed_dead_range = Speed{4},
          .circumference = Meter{0.205},
          .label = "left-wheel",
      },
      .width = Meter{0.102},
  };
};

Action str_to_action(const std::string &action_name, const Config &config)
{
  if (auto it = config.actions.find(action_name); it != config.actions.end())
  {
    return it->second;
  }

  return ActionType::None{};
}

void do_loop(Robot &robot, const Config &config)
{
  const auto input = common_utils::trim(io_utils::get_string());
  const auto tokens = common_utils::split(input);

  if (tokens.size() < 1)
  {
    io_utils::error("Not enough arguments");
    return;
  }

  const auto action_name = tokens.front();
  const auto parameters = common_utils::remove_first(tokens);

  const auto action = [&]
  {
    auto action = str_to_action(action_name, config);
    std::visit([&parameters](auto &action)
               { action.populate(parameters); }, action);
    return action;
  }();

  io_utils::info("Received: input: %s, action: %s", input.c_str(), to_string(action).c_str());

  std::visit([&](const auto &action)
             { action.apply(robot); }, action);
}

void setup()
{
  // inital setup in loop, to avoid using global state
}

void loop()
{
  const auto config = Config{};
  auto robot = Robot(config.robot_settings);

  io_utils::init(config.serial_baud, config.log_level);
  delay(config.delay_after_io_init.count());
  io_utils::debug("Initialization complete");

  while (true)
  {
    do_loop(robot, config);
  }
}