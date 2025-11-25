#pragma once

#include "common.h"
#include "geo_utils.h"

namespace robot_utils
{
    inline void move_fwd(Robot &robot, Meter distance)
    {
        robot.rotate(distance, distance, Speed{1});
    }

    inline void move_bwd(Robot &robot, Meter distance)
    {
        robot.rotate(-distance, -distance, Speed{1});
    }

    inline void rotate_left(Robot &robot, Degree angle)
    {
        auto sector_length = geo_utils::to_sector(angle, robot.width() / 2);
        robot.rotate(-sector_length, sector_length, Speed{1});
    }

    inline void rotate_right(Robot &robot, Degree angle)
    {
        auto sector_length = geo_utils::to_sector(angle, robot.width() / 2);
        robot.rotate(sector_length, -sector_length, Speed{1});
    }
}