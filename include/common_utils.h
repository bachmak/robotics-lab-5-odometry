#pragma once

#include <optional>
#include <string>
#include <vector>

namespace common_utils
{
    std::string trim(const std::string &str);
    std::vector<std::string> split(const std::string &s);

    std::optional<float> str_to_float(const std::string &str);
    float str_to_float(const std::string &str, float default_value);

    std::optional<bool> str_to_bool(const std::string &str);
    bool str_to_bool(const std::string &str, bool default_value);

    float str_to_float(const std::optional<std::string> &str, float default_value);
    float ema(float new_value, float prev_value, float alpha);
}