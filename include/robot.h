#pragma once

#include "wheel.h"

struct Wheels
{
    Wheel left;
    Wheel right;
};

class Robot
{
public:
    Robot(const Wheels &wheels) : wheels_(wheels) {}

public:
    void move(float distance, float cur_pos);
    void rotate(float angle, float cur_pos);

private:
    Wheels wheels_;
};
