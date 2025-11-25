#pragma once

#include "common.h"

namespace geo_utils
{
    Degree get_full_angle(Degree full_angle, Degree prev_full_angle);
    Meter to_distance(Degree angle, Meter circumference);
    Degree to_angle(Meter distance, Meter circumference);
    Meter to_sector(Degree angle, Meter radius);
}