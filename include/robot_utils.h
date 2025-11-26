#pragma once

#include "robot.h"
#include "common.h"
#include "geo_utils.h"

namespace robot_utils
{
    inline void move_fwd(Robot &robot, Meter distance, Speed speed)
    {
        robot.rotate(distance, distance, speed);
    }

    inline void move_bwd(Robot &robot, Meter distance, Speed speed)
    {
        robot.rotate(-distance, -distance, speed);
    }

    inline void rotate_left(Robot &robot, Degree angle, Speed speed)
    {
        auto sector_length = geo_utils::to_sector(angle, robot.width() / 2);
        robot.rotate(-sector_length, sector_length, speed);
    }

    inline void rotate_right(Robot &robot, Degree angle, Speed speed)
    {
        auto sector_length = geo_utils::to_sector(angle, robot.width() / 2);
        robot.rotate(sector_length, -sector_length, speed);
    }
}