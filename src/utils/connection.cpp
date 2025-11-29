#include "utils/connection.h"

#include "rmw_microros/ping.h"
#include "time_utils.h"

namespace utils::connection
{
    enum class State
    {
        WAITING,
        CONNECTED,
        DISCONNECTED,
    };

    State check_connection(time_utils::Timer &timer, Ms ping_timeout)
    {
        if (timer.is_over())
        {
            timer.reset();

            auto res = rmw_uros_ping_agent(ping_timeout.count(), 1);
            if (res == RMW_RET_OK)
            {
                return State::CONNECTED;
            }

            return State::DISCONNECTED;
        }

        return State::WAITING;
    }

    bool is_connected(time_utils::Timer &timer, Ms ping_timeout)
    {
        return check_connection(timer, ping_timeout) == State::CONNECTED;
    }

    bool is_disconnected(time_utils::Timer &timer, Ms ping_timeout)
    {
        return check_connection(timer, ping_timeout) == State::DISCONNECTED;
    }
}