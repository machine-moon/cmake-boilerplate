#include "Examples/cppzmq.h"
#include <iostream>
#include <zmq.hpp>

namespace Twiz
{
    void CppzmqDemo()
    {
        zmq::context_t ctx(1);
        zmq::socket_t const socket(ctx, zmq::socket_type::req);
        std::cout << "cppzmq socket created (REQ type)" << '\n';
    }
} // namespace Twiz
