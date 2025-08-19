#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

namespace Utils
{

    // -- Time Utilities --

    std::chrono::milliseconds GetCurrentTimeMillis();
    uint64_t GetTickCountMillis();
    std::string FormatDurationFromMillis(uint64_t milliseconds);
    std::string MillisToISO8601UTC(uint64_t millisFromEpoch);

    // -- Basic Directory Utilities --

    bool DirectoryExists(const std::string& directoryPath);
    bool FileExists(const std::string& filePath);
    bool CreateDirectory(const std::string& directoryPath);
    std::vector<std::string> ListFilesInDirectory(const std::string& directoryPath);
    std::string GetCurrentWorkingDirectory();

    // -- Network and Host Information --

    std::string GetHostName();
    std::string GetHostIP();
    std::vector<std::string> GetNetworkInterfaces();
    bool IsValidIPAddress(const std::string& ipAddress);
    std::string GetMACAddress(const std::string& interfaceName = "");
    int GetPortFromServiceName(const std::string& serviceName, const std::string& protocol = "tcp");

    // -- ID and UUID Generation --

    std::string GenerateUUID();

} // namespace Utils
