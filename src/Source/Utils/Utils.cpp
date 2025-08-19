#include "Utils/Utils.h"

#include <arpa/inet.h>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <exception>
#include <filesystem>
#include <ifaddrs.h>
#include <iomanip>
#include <ios>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <uuid/uuid.h>

namespace Utils
{

    // -- Time Utilities Implementation --

    std::chrono::milliseconds GetCurrentTimeMillis()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }

    uint64_t GetTickCountMillis()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    std::string FormatDurationFromMillis(uint64_t milliseconds)
    {
        uint64_t const days = milliseconds / (static_cast<uint64_t>(24 * 60 * 60 * 1000));
        milliseconds %= (static_cast<uint64_t>(24 * 60 * 60 * 1000));

        uint64_t const hours = milliseconds / (static_cast<uint64_t>(60 * 60 * 1000));
        milliseconds %= (static_cast<uint64_t>(60 * 60 * 1000));

        uint64_t const minutes = milliseconds / (static_cast<uint64_t>(60 * 1000));
        milliseconds %= (static_cast<uint64_t>(60 * 1000));

        uint64_t const seconds = milliseconds / 1000;
        milliseconds %= 1000;

        std::ostringstream oss;
        if (days > 0)
        {
            oss << days << "d ";
        }
        if (hours > 0)
        {
            oss << hours << "h ";
        }
        if (minutes > 0)
        {
            oss << minutes << "m ";
        }
        if (seconds > 0)
        {
            oss << seconds << "s ";
        }
        if (milliseconds > 0)
        {
            oss << milliseconds << "ms";
        }

        std::string result = oss.str();
        if (!result.empty() && result.back() == ' ')
        {
            result.pop_back();
        }

        return result.empty() ? "0ms" : result;
    }

    std::string MillisToISO8601UTC(uint64_t millisFromEpoch)
    {
        if (millisFromEpoch <= 0)
        {
            return "";
        }

        auto const seconds = static_cast<time_t>(millisFromEpoch / 1000);
        uint64_t const millis = millisFromEpoch % 1000;

        struct tm* utcTm = gmtime(&seconds);
        if (!utcTm)
        {
            return "";
        }

        std::ostringstream oss;
        oss << std::put_time(utcTm, "%Y-%m-%dT%H:%M:%S");
        if (millis > 0)
        {
            oss << "." << std::setfill('0') << std::setw(3) << millis;
        }
        oss << "Z";

        return oss.str();
    }

    // -- Basic Directory Utilities Implementation --

    bool DirectoryExists(const std::string& directoryPath)
    {
        return std::filesystem::exists(directoryPath) && std::filesystem::is_directory(directoryPath);
    }

    bool FileExists(const std::string& filePath)
    {
        return std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath);
    }

    bool CreateDirectory(const std::string& directoryPath)
    {
        try
        {
            return std::filesystem::create_directories(directoryPath);
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    std::vector<std::string> ListFilesInDirectory(const std::string& directoryPath)
    {
        std::vector<std::string> files;
        try
        {
            for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
            {
                files.push_back(entry.path().filename().string());
            }
        }
        catch (const std::exception&)
        {
            // Directory doesn't exist or can't be read
        }
        return files;
    }

    std::string GetCurrentWorkingDirectory()
    {
        try
        {
            return std::filesystem::current_path().string();
        }
        catch (const std::exception&)
        {
            return "";
        }
    }

    // -- Network and Host Information Implementation --

    std::string GetHostName()
    {
        static const size_t hostnameBufferSize = 256;
        std::array<char, hostnameBufferSize> hostnameArray = {};

        if (gethostname(hostnameArray.data(), hostnameArray.size()) == 0)
        {
            return {hostnameArray.data()};
        }
        return "unknown";
    }

    std::string GetHostIP()
    {
        struct ifaddrs *ifaddr = nullptr, *ifa = nullptr;
        char host[NI_MAXHOST];

        if (getifaddrs(&ifaddr) == -1)
        {
            return "127.0.0.1";
        }

        for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
        {
            if (ifa->ifa_addr == nullptr)
            {
                continue;
            }

            if (ifa->ifa_addr->sa_family == AF_INET && !(ifa->ifa_flags & IFF_LOOPBACK))
            {
                if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST) == 0)
                {
                    freeifaddrs(ifaddr);
                    return std::string(host);
                }
            }
        }

        freeifaddrs(ifaddr);
        return "127.0.0.1";
    }

    std::vector<std::string> GetNetworkInterfaces()
    {
        std::vector<std::string> interfaces;
        struct ifaddrs *ifaddr = nullptr, *ifa = nullptr;

        if (getifaddrs(&ifaddr) == -1)
        {
            return interfaces;
        }

        for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
        {
            if (ifa->ifa_name != nullptr)
            {
                interfaces.emplace_back(ifa->ifa_name);
            }
        }

        freeifaddrs(ifaddr);
        return interfaces;
    }

    bool IsValidIPAddress(const std::string& ipAddress)
    {
        struct sockaddr_in sockAddr{};
        return inet_pton(AF_INET, ipAddress.c_str(), &(sockAddr.sin_addr)) != 0;
    }

    std::string GetMACAddress(const std::string& interfaceName)
    {
        std::string const interface = interfaceName.empty() ? "eth0" : interfaceName;

        int const sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0)
        {
            return "";
        }

        struct ifreq ifr{};
        memset(&ifr, 0, sizeof(ifr));
        strncpy(ifr.ifr_name, interface.c_str(), IFNAMSIZ - 1);

        if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0)
        {
            close(sock);
            return "";
        }

        close(sock);

        auto* mac = reinterpret_cast<unsigned char*>(ifr.ifr_hwaddr.sa_data);
        std::ostringstream oss;
        for (int i = 0; i < 6; ++i)
        {
            if (i > 0)
            {
                oss << ":";
            }
            oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(mac[i]);
        }

        return oss.str();
    }

    int GetPortFromServiceName(const std::string& serviceName, const std::string& protocol)
    {
        struct servent* service = getservbyname(serviceName.c_str(), protocol.c_str());
        return service ? ntohs(service->s_port) : -1;
    }

    // -- ID and UUID Generation Implementation --

    std::string GenerateUUID()
    {
#ifndef WIN32
        uuid_t uuid;
        uuid_generate(uuid);

        char uuidStr[37];
        uuid_unparse(uuid, uuidStr);

        return std::string(uuidStr);
#else
        // Fallback for Windows - simple random ID
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 15);

        std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
        for (char& c : uuid)
        {
            if (c == 'x')
            {
                c = "0123456789abcdef"[dis(gen)];
            }
            else if (c == 'y')
            {
                c = "89ab"[dis(gen) % 4];
            }
        }
        return uuid;
#endif
    }

} // namespace Utils