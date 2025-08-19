#pragma once

#include "Constants.h"
#include "Utils/ThreadConcepts.h"
#include "Utils/Utils.h"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <string>
#include <thread>

struct ThreadMetrics
{
    uint64_t m_lastHeartbeatEpochMS;
    uint64_t m_appLaunchTick;
    uint64_t m_errorCount{};
    uint64_t m_tickCount{};
    double m_messageRate{};
    uint64_t m_bytesProcessed{0};

    ThreadMetrics()
    {
        uint64_t now = Utils::GetTickCountMillis();
        m_lastHeartbeatEpochMS = now;
        m_appLaunchTick = now;
    }
};

struct ThreadProperties
{
    ThreadMetrics m_metrics{};
    uint16_t m_heartbeatIntervalMS{Constants::heartbeatIntervalMs};
};

template<typename T, typename U = decltype(T::m_metrics)>
requires ThreadCompatible<T, U, ThreadProperties, ThreadMetrics>
class CThreadBase
{
public:
    explicit CThreadBase(const T& properties)
        : m_properties(properties)
    {
    }

    CThreadBase() = delete;
    CThreadBase(const CThreadBase&) = delete;
    CThreadBase(CThreadBase&&) = delete;
    CThreadBase& operator=(const CThreadBase&) = delete;
    CThreadBase& operator=(CThreadBase&&) = delete;

    virtual ~CThreadBase() { Stop(); }

    virtual void Stop()
    {
        if (m_isRunning.load())
        {
            m_isRunning.store(false);
        }
        if (m_self.joinable())
        {
            m_self.join();
        }
    }
    virtual bool Start() = 0;

    [[nodiscard]] virtual const U& GetMetrics() const { return m_properties.m_metrics; }
    [[nodiscard]] virtual const T& GetProperties() const { return m_properties; }

    [[nodiscard]] virtual bool IsRunning() const { return m_isRunning.load(); }
    [[nodiscard]] virtual const std::string& GetUUID() const { return m_uuid; }

protected:
    virtual void SendHeartbeat()
    {
        uint64_t now = Utils::GetTickCountMillis();
        if (now - m_properties.m_metrics.m_lastHeartbeatEpochMS >= m_properties.m_heartbeatIntervalMS)
        {
            m_properties.m_metrics.m_lastHeartbeatEpochMS = now;
        }
    }
    virtual void Run() = 0;
    virtual void Tick() = 0;

    std::thread m_self;
    std::atomic<bool> m_isRunning{false};
    std::string m_uuid{Utils::GenerateUUID()};
    T m_properties{};
};
