#include "common.h"

#include <Arduino.h>

namespace time_utils
{
    class StopWatch
    {
    public:
        Ms time_passed(Ms curr_ts = Ms{millis()}) const
        {
            return curr_ts - start_ts_;
        }

    private:
        Ms start_ts_ = Ms{millis()};
    };

    class IterationStopWatch
    {
    public:
        void tick(Ms curr_ts = Ms{millis()})
        {
            last_it_ = (curr_ts - last_ts_);
            total_ += last_it_;
            iterations_++;
            last_ts_ = curr_ts;
        }

        Ms average() const
        {
            return Ms{static_cast<int>(static_cast<double>(total_.count()) / iterations_)};
        }

        Ms last_it() const { return last_it_; }

    private:
        Ms last_ts_ = Ms{millis()};
        Ms total_ = {};
        Ms last_it_ = {};
        int iterations_ = 0;
    };
}