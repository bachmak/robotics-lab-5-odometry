#pragma once

#include <rclc/types.h>
#include <rclc/node.h>

#include <string_view>

namespace rclc
{
    class Node;

    class Support
    {
    public:
        static Support &getInstance();

        Node create_node(const char *name);

    private:
        Support();

        rcl_allocator_t allocator_;
        rclc_support_t support_;
    };

    class Node
    {
    public:
        Node(rclc_support_t &support, const char *name);

    private:
        rcl_node_t impl_;
    };
}
