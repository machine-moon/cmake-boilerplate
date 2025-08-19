#include "Examples/spdlog.h"
#include <iostream>
#include <numbers>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>

namespace Twiz
{

    void BasicLoggingDemo()
    {
        std::cout << "\n--- Basic Logging Demo ---" << '\n';

        spdlog::info("This is an info message");
        spdlog::warn("This is a warning message");
        spdlog::error("This is an error message");
        spdlog::debug("This is a debug message");
        spdlog::critical("This is a critical message");

        std::cout << "Basic logging completed" << '\n';
    }

    void LogLevelsDemo()
    {
        std::cout << "\n--- Log Levels Demo ---" << '\n';

        spdlog::set_level(spdlog::level::trace);
        spdlog::trace("Trace level message");
        spdlog::debug("Debug level message");
        spdlog::info("Info level message");
        spdlog::warn("Warning level message");
        spdlog::error("Error level message");
        spdlog::critical("Critical level message");

        spdlog::set_level(spdlog::level::info);
        std::cout << "Log levels demo completed" << '\n';
    }

    void FormattingDemo()
    {
        std::cout << "\n--- Formatting Demo ---" << '\n';

        std::string name = "spdlog";
        int version = 1;
        double pie = std::numbers::pi;

        spdlog::info("Library: {}, Version: {}", name, version);
        spdlog::info("Pi value: {:.2f}", pie);
        spdlog::info("Binary: {:b}, Hex: {:x}", 42, 255);

        std::cout << "Formatting demo completed" << '\n';
    }

    void FileLoggingDemo()
    {
        std::cout << "\n--- File Logging Demo ---" << '\n';

        try
        {
            auto fileLogger = spdlog::basic_logger_mt("file_logger", "logs/example.log");
            fileLogger->info("This message is written to a file");
            fileLogger->warn("Warning message in file");
            fileLogger->error("Error message in file");

            spdlog::drop("file_logger");
            std::cout << "File logging demo completed - check logs/example.log" << '\n';
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            spdlog::error("Log initialization failed: {}", ex.what());
        }
    }

    void ConsoleLoggingDemo()
    {
        std::cout << "\n--- Console Logging Demo ---" << '\n';

        auto consoleLogger = spdlog::stdout_color_mt("console_logger");
        consoleLogger->info("Colored console message");
        consoleLogger->warn("Colored warning message");
        consoleLogger->error("Colored error message");

        spdlog::drop("console_logger");
        std::cout << "Console logging demo completed" << '\n';
    }

    void RunSpdlogShowcase()
    {
        std::cout << "\n=== SPDLOG LOGGING SHOWCASE ===" << '\n';
        std::cout << "Fast, thread-safe logging library" << '\n';
        std::cout << "Perfect for applications requiring high-performance logging\n" << '\n';

        BasicLoggingDemo();
        LogLevelsDemo();
        FormattingDemo();
        FileLoggingDemo();
        ConsoleLoggingDemo();

        std::cout << "\nspdlog showcase completed!" << '\n';
    }

} // namespace Twiz
