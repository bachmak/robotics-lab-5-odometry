#include "app/lab_6.h"

#include "ros_oop/support.h"
#include "ros_oop/node.h"
#include "ros_oop/publisher.h"
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
        auto publisher = ros::Publisher<int32_t>{node, config.topic_name};
        auto timer_callback = [&](int64_t last_call_time)
        {
            static auto counter = 0;
            publisher.publish(counter++);
        };

        auto timer = ros::Timer{support, config.timer_period, timer_callback};

        auto executables = std::vector<ros::Executable>{
            &timer,
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

        while (true)
        {
            do_loop(config);
        }
    }
}