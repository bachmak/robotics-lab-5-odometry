#pragma once

#include "io_utils.h"

#include <rcl/types.h>

namespace ros
{
    inline void rcc_check(rcl_ret_t ret)
    {
        if (ret != RCL_RET_OK)
        {
            io_utils::error("Error loop entered. Error: %d", ret);
            while (1)
            {
            }
        }
    }
}