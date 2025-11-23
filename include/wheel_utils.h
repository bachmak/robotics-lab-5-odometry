#pragma once

class Wheel;
class WheelAttachment;

namespace wheel_utils
{
    float get_full_angle(const Wheel &w, const float prev_full_angle);
    float angle_to_distance(const Wheel &w, float angle);
    float distance_to_angle(const Wheel &w, float distance);

    void stop(Wheel &w, WheelAttachment &wa);
    void rotate(Wheel &w, WheelAttachment &wa, int speed);
    void change_speed(Wheel &w, WheelAttachment &wa, int delta_speed);
}