#include "app/lab_6.h"

#include "ros_oop/support.h"
#include "ros_oop/node.h"
#include "ros_oop/subscription.h"
#include "ros_oop/executor.h"
#include "ros_oop/timer.h"
#include "io_utils.h"
#include "time_utils.h"
#include "utils/connection.h"

#include <Arduino.h>

namespace lab_6
{
    struct Config
    {
        io_utils::Settings io_setings{
            .serial_baud = 115200,
            .serial_redirect = io_utils::SerialRedirect::MICRO_ROS,
            .delay_after_init = Ms{2000},
        };

        const char *node_name = "micro_ros_platformio_node";
        const char *topic_name = "micro_ros_platformio_node_publisher";

        Ms ping_interval{500};
        Ms ping_timeout{100};

        Ms timer_period{1000};
        Ms loop_delay{100};
        Ms spin_timeout{100};
        Ms connection_check_period{500};

        Pin blink_pin{13};
    };

    static const auto config = Config{};

    void do_loop(const Config &config)
    {
        auto ping_timer = time_utils::Timer{
            config.ping_interval,
            // adjusted start point for timer to avoid waiting the first time
            -config.ping_interval,
        };
        while (!utils::connection::is_connected(ping_timer, config.ping_timeout))
        {
        }

        auto support = ros::Support{};
        auto node = ros::Node{support, config.node_name};
        auto subscription_callback = [&config](int32_t data)
        {
            digitalWrite(config.blink_pin.v, data);
        };

        auto subscription = ros::Subscription<int32_t>{
            node,
            "micro_ros_arduino_subscriber",
            subscription_callback};

        auto executables = std::vector<ros::Executable>{
            &subscription.base(),
        };

        auto executor = ros::Executor{support, executables};

        while (!utils::connection::is_disconnected(ping_timer, config.ping_timeout))
        {
            delay(config.loop_delay.count());
            executor.spin_some(config.spin_timeout);
        }
    }

    void run()
    {
        const auto config = Config{};

        io_utils::init(config.io_setings);

        pinMode(config.blink_pin.v, OUTPUT);

        while (true)
        {
            do_loop(config);
        }
    }
}