#include <Arduino.h>

#include <chrono>

namespace pwm_utils
{
    struct CycleDuration
    {
        std::chrono::microseconds high;
        std::chrono::microseconds full;
    };

    float to_duty_cycle(CycleDuration duration);
    CycleDuration measure_pwm_duration(int pin);
    CycleDuration measure_pwm_duration(int pin,
                                       std::chrono::microseconds min,
                                       std::chrono::microseconds max);
}