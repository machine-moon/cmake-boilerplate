#include "boost_example.h"
#include <boost/version.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <string>

namespace twiz_examples {
void show_boost() {
    std::cout << "Boost version: " << BOOST_LIB_VERSION << std::endl;
}

void beast_buffer_example() {
    boost::beast::flat_buffer buffer;
    std::string data = "Hello, Beast!";
    buffer.commit(boost::asio::buffer_copy(buffer.prepare(data.size()), boost::asio::buffer(data)));
    std::cout << "Buffer size: " << buffer.size() << std::endl;
}

void beast_http_request_example() {
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, "/", 11};
    req.set(boost::beast::http::field::host, "example.com");
    req.set(boost::beast::http::field::user_agent, "Boost.Beast/1.0");
    std::cout << "HTTP request target: " << req.target() << std::endl;
}
}
