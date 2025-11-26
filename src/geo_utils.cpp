#include "geo_utils.h"

#include <math.h>

namespace geo_utils
{
    namespace
    {
        Degree normalize(Degree d)
        {
            const auto v = fmod(d.v, 360.0f);
            if (v < 0)
            {
                return Degree{v + 360.0f};
            }
            return Degree{v};
        }

        constexpr auto pi = static_cast<float>(M_PI);
    }

    Degree get_full_angle(const Degree full_angle, const Degree prev_full_angle)
    {
        const auto prev_angle = normalize(prev_full_angle);
        const auto curr_angle = normalize(full_angle);

        const auto prev_turns = static_cast<int>(floor(prev_full_angle.v / 360.0f));
        const auto curr_turns = [&]
        {
            constexpr auto min = Degree{90};
            constexpr auto max = Degree{270};

            if (curr_angle < min && prev_angle > max)
                return prev_turns + 1;

            if (prev_angle < min && curr_angle > max)
                return prev_turns - 1;

            return prev_turns;
        }();

        const auto curr_full_angle = Degree{curr_turns * 360 + curr_angle.v};
        return curr_full_angle;
    }

    Meter to_distance(Degree angle, Meter circumference)
    {
        return Meter{angle.v / 360 * circumference.v};
    }

    Degree to_angle(Meter distance, Meter circumference)
    {
        return Degree{distance / circumference * 360};
    }

    Meter to_sector(Degree angle, Meter radius)
    {
        return radius * pi * angle.v / 180.0f;
    }
}
