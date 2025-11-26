#pragma once

#include <optional>
#include <string>
#include <vector>

namespace common_utils
{
    template <class... Ts>
    struct overloads : Ts...
    {
        using Ts::operator()...;
    };

    template <class... Ts>
    overloads(Ts...) -> overloads<Ts...>;

    std::string trim(const std::string &str);
    std::vector<std::string> split(const std::string &s);

    std::optional<float> str_to_float(const std::string &str);
    float str_to_float(const std::string &str, float default_value);

    std::optional<bool> str_to_bool(const std::string &str);
    bool str_to_bool(const std::string &str, bool default_value);

    float str_to_float(const std::optional<std::string> &str, float default_value);
    float ema(float new_value, float prev_value, float alpha);

    template <typename T>
    std::vector<T> remove_first(const std::vector<T> &v, size_t n = 1)
    {
        if (v.size() > n - 1)
        {
            auto copy = v;
            for (size_t i = 0; i < n; i++)
            {
                copy.erase(copy.begin());
            }
            return copy;
        }

        return v;
    }
}