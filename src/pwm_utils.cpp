#include "pwm_utils.h"

#include <Arduino.h>

namespace pwm_utils
{
    float to_duty_cycle(CycleDuration duration)
    {
        return static_cast<float>(duration.high.count()) / duration.full.count();
    }

    CycleDuration measure_pwm_duration(int pin)
    {
        auto high = std::chrono::microseconds{pulseIn(pin, HIGH)};
        auto low = std::chrono::microseconds{pulseIn(pin, LOW)};
        auto full = high + low;

        return {high, full};
    }

    CycleDuration measure_pwm_duration(int pin,
                                       std::chrono::microseconds min,
                                       std::chrono::microseconds max)
    {
        while (true)
        {
            auto duration = measure_pwm_duration(pin);
            if (duration.full > min && duration.full < max)
            {
                return duration;
            }
        }
    }
}