#include "robot.h"

#include "wheel_utils.h"
#include "io_utils.h"

#include <Arduino.h>

constexpr auto eps = 0.00001f;

void Robot::move(const float target_pos, const float init_pos)
{
    const auto direction = init_pos < target_pos ? 1 : -1;

    auto &[left, right] = wheels_;
    auto left_wa = left.attach();
    auto right_wa = right.attach();

    auto angle_left = right.read_angle();
    auto angle_right = left.read_angle();

    wheel_utils::rotate(left, left_wa, 1 * direction);
    wheel_utils::rotate(right, right_wa, -1 * direction);

    auto cur_pos = init_pos;

    while (fabs(cur_pos - target_pos) > eps)
    {
        // TODO: complete implementation
        delay(2000);

        angle_left = wheel_utils::get_full_angle(left, angle_left);
        angle_right = wheel_utils::get_full_angle(right, angle_right);

        auto cur_pos_left = wheel_utils::angle_to_distance(left, angle_left);
        auto cur_pos_right = wheel_utils::angle_to_distance(right, angle_right);

        io_utils::debug("cur_pos: left=%f, right=%f", cur_pos_left, cur_pos_right);

        cur_pos = cur_pos_left;
    }

    wheel_utils::stop(left, left_wa);
    wheel_utils::stop(right, right_wa);
}

void Robot::rotate(float angle, float cur_pos)
{
    // TODO: complete implementation
    (void)angle;
    (void)cur_pos;
}
