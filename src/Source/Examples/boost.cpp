#include "Examples/boost.h"
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/optional.hpp>
#include <chrono>
#include <iostream>

namespace Twiz
{

    void UseBoostOptional()
    {
        boost::optional<int> value;
        value = 42;
        std::cout << "Boost.Optional value: " << *value << '\n';
    }

    void ShowBeast()
    {
        namespace Beast = boost::beast;
        Beast::http::request<Beast::http::string_body> req{Beast::http::verb::get, "/", 11};
        req.body() = "Hello, Beast!";
        req.prepare_payload();
        std::cout << "Beast HTTP request target: " << req.target() << '\n';
    }

    void ShowAsio()
    {
        boost::asio::io_context ioContext;
        boost::asio::steady_timer timer(ioContext, std::chrono::milliseconds(100));
        timer.async_wait([](const boost::system::error_code& errorCode) {
            if (!errorCode)
            {
                std::cout << "Asio timer expired" << '\n';
            }
        });
        ioContext.run();
    }

} // namespace Twiz
