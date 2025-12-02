#pragma once

#include "ros_oop/subscription.h"
#include "wheely.h"
#include "common_utils.h"

class WheelyConfigurator
{
public:
    explicit WheelyConfigurator(Wheely &wheely, ros::Node &node, const char *topic_name)
        : wheely_(wheely),
          subscription_(node,
                        topic_name,
                        [this](const std::string &str)
                        { configure(str); })
    {
    }

    auto &subscription() { return subscription_; }

private:
    void configure(const std::string &str)
    {
        const auto tokens = common_utils::split(str);
        if (tokens.size() != 2)
        {
            return;
        }

        const auto setting = tokens[0];
        const auto value = common_utils::str_to_float(tokens[1]);
        if (!value.has_value())
        {
            return;
        }

        wheely_.configure(setting, *value);
    }

private:
    Wheely &wheely_;
    ros::Subscription<std::string> subscription_;
};