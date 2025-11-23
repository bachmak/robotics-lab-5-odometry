#include "wheel_utils.h"

#include "wheel.h"

#include <math.h>

namespace wheel_utils
{
    float get_full_angle(const Wheel &wheel, const float prev_full_angle)
    {
        const auto prev_angle = fmod(prev_full_angle, 360.0);
        const auto curr_angle = wheel.read_angle();

        const auto prev_turns = static_cast<int>(prev_full_angle / 360.0);
        const auto curr_turns = [&]
        {
            if (curr_angle < 90 && prev_angle > 270)
            {
                return prev_turns + 1;
            }

            if (prev_angle < 90 && curr_angle > 270)
            {
                return prev_turns - 1;
            }

            return prev_turns;
        }();

        const auto curr_full_angle = curr_turns * 360 + curr_angle;
        return curr_full_angle;
    }

    float angle_to_distance(const Wheel &wheel, float angle)
    {
        return angle / 360 * wheel.circumference();
    }

    float distance_to_angle(const Wheel &wheel, float distance)
    {
        return distance / wheel.circumference() * 360;
    }

    void stop(Wheel &wheel, WheelAttachment &wa)
    {
        wheel.rotate(wa, 0);
    }

    void rotate(Wheel &wheel, WheelAttachment &wa, int speed)
    {
        wheel.rotate(wa, speed);
    }

    void change_speed(Wheel &wheel, WheelAttachment &wa, int delta_speed)
    {
        auto speed = wheel.current_speed() + delta_speed;
        wheel.rotate(wa, speed);
    }
}
