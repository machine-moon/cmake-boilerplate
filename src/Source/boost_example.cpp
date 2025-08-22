#include "boost_example.h"
#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include <boost/filesystem.hpp> // Compiled (static or dynamic)
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/optional.hpp> // Header-only
#include <boost/regex.hpp>
#include <boost/regex.hpp> // Compiled (static or dynamic)
#include <boost/version.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace twiz
{

// 1. Header-only Boost library example
void useBoostOptional()
{
    boost::optional<int> value;
    if (!value)
    {
        value = 42;
    }
    std::cout << "Boost.Optional value: " << *value << std::endl;
}

// 2. Compiled Boost library example (can be linked statically)
void useBoostFilesystem()
{
    boost::filesystem::path p = "/tmp/testfile.txt";
    std::cout << "Filename using Boost.Filesystem: " << p.filename() << std::endl;
}

// 3. Compiled Boost library example (can be linked dynamically)
void useBoostRegex()
{
    boost::regex re("\\d+");
    std::string s = "Boost version: 189";
    if (boost::regex_search(s, re))
    {
        std::cout << "Boost.Regex found a number in the string." << std::endl;
    }
}

void fun()
{
    useBoostOptional();
    useBoostFilesystem();
    useBoostRegex();

}

void run_boost_networking_suite()
{
    std::cout << "\n=== BOOST LIBRARY COMPREHENSIVE SUITE ===" << std::endl;
    std::cout << "Boost Version: " << BOOST_VERSION / 100000 << "." << BOOST_VERSION / 100 % 1000
              << "." << BOOST_VERSION % 100 << std::endl;
    std::cout << "Demonstrating various Boost header-only capabilities:\n" << std::endl;

    // Run all Boost examples
    boost_string_processing_demo();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    boost_format_demo();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    boost_regex_demo();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    boost_optional_any_demo();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    boost_lexical_cast_demo();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "\nBoost library suite completed successfully!" << std::endl;
}

void boost_string_processing_demo()
{
    std::cout << "\n--- String Processing with Boost.Algorithm ---" << std::endl;

    std::string text = "  Hello, World! This is a Boost string processing demo.  ";
    std::cout << "Original: '" << text << "'" << std::endl;

    // Trim whitespace
    std::string trimmed = text;
    boost::trim(trimmed);
    std::cout << "Trimmed: '" << trimmed << "'" << std::endl;

    // Convert to uppercase
    std::string upper = trimmed;
    boost::to_upper(upper);
    std::cout << "Uppercase: '" << upper << "'" << std::endl;

    // Split into words
    std::vector<std::string> words;
    boost::split(words, trimmed, boost::is_any_of(" ,.!"), boost::token_compress_on);
    std::cout << "Words (" << words.size() << "): ";
    for (const auto& word : words)
    {
        if (!word.empty())
        {
            std::cout << "[" << word << "] ";
        }
    }
    std::cout << std::endl;

    // Join with different separator
    std::string joined = boost::join(words, " | ");
    std::cout << "Joined: " << joined << std::endl;

    // Replace all occurrences
    std::string replaced = trimmed;
    boost::replace_all(replaced, "Boost", "Amazing Boost");
    std::cout << "Replaced: " << replaced << std::endl;
}

void boost_format_demo()
{
    std::cout << "\n--- Advanced Formatting with Boost.Format ---" << std::endl;

    try
    {
        // Basic formatting
        boost::format fmt1("Hello %1%, you are %2% years old!");
        fmt1 % "Alice" % 25;
        std::cout << "Basic: " << fmt1 << std::endl;

        // Numeric formatting
        boost::format fmt2("Pi = %|1$+8.3f|, Hex = %|2$#08x|");
        fmt2 % 3.14159 % 255;
        std::cout << "Numeric: " << fmt2 << std::endl;

        // Positional arguments
        boost::format fmt3("%2% is %1% times better than %3%!");
        fmt3 % 10 % "Boost" % "alternatives";
        std::cout << "Positional: " << fmt3 << std::endl;

        // Table formatting
        std::cout << "\nTable formatting:" << std::endl;
        boost::format table_fmt("| %|1$-12s| %|2$8.2f| %|3$6d| |");

        std::cout << table_fmt % "Item" % "Price" % "Qty" << std::endl;
        std::cout << std::string(30, '-') << std::endl;
        std::cout << table_fmt % "Widget" % 19.99 % 5 << std::endl;
        std::cout << table_fmt % "Gadget" % 149.50 % 2 << std::endl;
        std::cout << table_fmt % "Tool" % 75.25 % 1 << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Format error: " << e.what() << std::endl;
    }
}

void boost_regex_demo()
{
    std::cout << "\n--- Regular Expressions with Boost.Regex ---" << std::endl;

    try
    {
        std::string text =
            "Contact us at: email@example.com, phone: (555) 123-4567, or visit www.example.com";
        std::cout << "Text: " << text << std::endl;

        // Email regex
        boost::regex email_regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        boost::smatch email_match;
        if (boost::regex_search(text, email_match, email_regex))
        {
            std::cout << "Found email: " << email_match[0] << std::endl;
        }

        // Phone regex
        boost::regex phone_regex(R"(\((\d{3})\)\s*(\d{3})-(\d{4}))");
        boost::smatch phone_match;
        if (boost::regex_search(text, phone_match, phone_regex))
        {
            std::cout << "Found phone: " << phone_match[0] << std::endl;
            std::cout << "  Area code: " << phone_match[1] << std::endl;
            std::cout << "  Exchange: " << phone_match[2] << std::endl;
            std::cout << "  Number: " << phone_match[3] << std::endl;
        }

        // URL regex
        boost::regex url_regex(R"((?:https?://)?(?:www\.)?([a-zA-Z0-9.-]+\.[a-zA-Z]{2,}))");
        boost::smatch url_match;
        if (boost::regex_search(text, url_match, url_regex))
        {
            std::cout << "Found URL: " << url_match[0] << std::endl;
            std::cout << "  Domain: " << url_match[1] << std::endl;
        }

        // Replace with regex
        std::string censored = boost::regex_replace(text, email_regex, "[EMAIL]");
        censored = boost::regex_replace(censored, phone_regex, "[PHONE]");
        std::cout << "Censored: " << censored << std::endl;
    }
    catch (const boost::regex_error& e)
    {
        std::cout << "Regex error: " << e.what() << std::endl;
    }
}

void boost_optional_any_demo()
{
    std::cout << "\n--- Optional and Any with Boost ---" << std::endl;

    // Boost.Optional demo
    std::cout << "Optional demo:" << std::endl;
    boost::optional<int> maybe_value;
    std::cout << "Empty optional has value: " << (maybe_value ? "yes" : "no") << std::endl;

    maybe_value = 42;
    std::cout << "Set optional has value: " << (maybe_value ? "yes" : "no") << std::endl;
    std::cout << "Value: " << *maybe_value << std::endl;

    auto safe_divide = [](double a, double b) -> boost::optional<double> {
        if (b == 0.0)
            return boost::none;
        return a / b;
    };

    auto result1 = safe_divide(10.0, 2.0);
    auto result2 = safe_divide(10.0, 0.0);

    std::cout << "10/2 = " << (result1 ? std::to_string(*result1) : "undefined") << std::endl;
    std::cout << "10/0 = " << (result2 ? std::to_string(*result2) : "undefined") << std::endl;

    // Boost.Any demo
    std::cout << "\nAny demo:" << std::endl;
    std::vector<boost::any> values;
    values.push_back(42);
    values.push_back(std::string("Hello"));
    values.push_back(3.14);
    values.push_back(true);

    for (size_t i = 0; i < values.size(); ++i)
    {
        const boost::any& val = values[i];
        std::cout << "Value " << i << " type: " << val.type().name();

        if (val.type() == typeid(int))
        {
            std::cout << ", value: " << boost::any_cast<int>(val);
        }
        else if (val.type() == typeid(std::string))
        {
            std::cout << ", value: " << boost::any_cast<std::string>(val);
        }
        else if (val.type() == typeid(double))
        {
            std::cout << ", value: " << boost::any_cast<double>(val);
        }
        else if (val.type() == typeid(bool))
        {
            std::cout << ", value: " << (boost::any_cast<bool>(val) ? "true" : "false");
        }
        std::cout << std::endl;
    }
}

void boost_lexical_cast_demo()
{
    std::cout << "\n--- Type Conversions with Boost.LexicalCast ---" << std::endl;

    try
    {
        // String to numeric conversions
        std::string number_str = "123.45";
        double number = boost::lexical_cast<double>(number_str);
        std::cout << "String '" << number_str << "' to double: " << number << std::endl;

        // Numeric to string conversions
        int value = 42;
        std::string value_str = boost::lexical_cast<std::string>(value);
        std::cout << "Int " << value << " to string: '" << value_str << "'" << std::endl;

        // Boolean conversions
        bool flag = true;
        std::string flag_str = boost::lexical_cast<std::string>(flag);
        std::cout << "Bool " << flag << " to string: '" << flag_str << "'" << std::endl;

        // Array of conversions
        std::vector<std::string> str_numbers = {"10", "20", "30", "40", "50"};
        std::vector<int> numbers;

        for (const auto& str : str_numbers)
        {
            numbers.push_back(boost::lexical_cast<int>(str));
        }

        std::cout << "Converted array: ";
        for (int num : numbers)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        // Sum the converted numbers
        int sum = 0;
        for (int num : numbers)
        {
            sum += num;
        }
        std::cout << "Sum: " << sum << std::endl;
    }
    catch (const boost::bad_lexical_cast& e)
    {
        std::cout << "Conversion error: " << e.what() << std::endl;
    }
}

} // namespace twiz
