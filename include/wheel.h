#pragma once

#include <Servo.h>

#include <chrono>
#include <string>

struct WheelSettings
{
    int control_pin = 0;
    int feedback_pin = 0;

    int min_pwm = 40;
    int stop_pwm = 90;
    int max_pwm = 150;

    int speed_dead_range = 5;

    float circumference = 0.22;

    std::chrono::microseconds feedback_pwm_min{1000};
    std::chrono::microseconds feedback_pwm_max{1200};

    float feedback_pwm_duty_cycle_min = 0.029;
    float feedback_pwm_duty_cycle_max = 0.971;

    std::string label = "default-wheel";
};

class WheelAttachment
{
public:
    WheelAttachment(Servo &servo, int pin) : servo(servo) { servo.attach(pin); }
    ~WheelAttachment() { servo.detach(); }

    WheelAttachment(const WheelAttachment &) = delete;
    WheelAttachment &operator=(const WheelAttachment &) = delete;

private:
    friend class Wheel;
    Servo &servo;
};

class Wheel
{
public:
    explicit Wheel(const WheelSettings &settings);

public:
    float circumference() const { return settings_.circumference; }
    int current_speed() const { return current_speed_; }

    WheelAttachment attach() { return WheelAttachment(servo_, settings_.control_pin); }

    void rotate(WheelAttachment &wa, int speed);
    float read_angle() const;

private:
    Servo servo_;
    WheelSettings settings_;
    int current_speed_;
};
