#pragma once
#include <cstdint>
#include <jsoncons/json.hpp>

struct Message
{
    uint64_t m_timestamp{};
    uint64_t m_id{};
    jsoncons::json m_payload;
    bool m_isProcessed{false};
};
