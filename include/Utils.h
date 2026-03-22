#ifndef AIRGEAD_UTILS
#define AIRGEAD_UTILS
/**
 * @file Utils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 15, 2026
 *
 * @brief Utility functions for Airgead banking application.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Outputs a @ref std::string with center alignment to the console.
 *
 * @param str       The string to print.
 * @param lineWidth The total width of the console output.
 * @param fill      The fill to use for padding the left and right sides.
 */
inline void printCentered(const std::string& str, const int lineWidth, const char fill = ' ')
{
    int totalInside = lineWidth; // NOTE: Removed - 2
    int leftPadding = static_cast<int>(totalInside - str.length()) / 2;
    int rightPadding = static_cast<int>(totalInside - str.length() - leftPadding);

    std::cout << std::setfill(fill) << std::setw(leftPadding) << "" << str << std::setw(rightPadding) << "";
}


/**
 * @brief Outputs a table header to the screen.
 *
 * @param str       The string to print.
 * @param lineWidth The total width of the console output.
 */
inline void printTableHeader(const std::string& str, const int lineWidth)
{
    std::cout << std::setw(lineWidth);
    printCentered(str, lineWidth);
    std::cout << "\n" << std::setw(lineWidth) << std::setfill('=') << "" << "\n";
}


/**
 * @brief Formats an amount to a currency with 1/100th precision.
 *        Adds currency symbol.
 *
 * @param amount The amount to format.
 *
 * @return The formatted amount.
 */
inline std::string formatCurrency(float amount)
{
    std::stringstream data;
    data << CURRENCY_SYMBOL;
    data << std::setprecision(2);
    data << std::fixed;
    data << amount;

    return data.str();
}


/**
 * @brief Briefly suspend the program, waiting for user input before continuing the program.
 */
inline void suspendInput()
{
    std::cout << CONSOLE_COLOR; // Configures console to print in color of the config.
    std::cout << "Press any key to continue...";
    std::cin.get();
    std::cout << "\n\n\n\n";
    std::cout << CONSOLE_COLOR_RESET << "\n"; // Clears the console color.
}


/**
 * @brief Clears the console using platform specific commands.
 *        `cls` on Windows an `clear` on macOS/Linux/Unix.
 */
inline void clearScreen()
{
#ifdef _WIN32 // Preprocessor definition for Windows based operating system.
    std::system("cls");
#else
    std::system("clear");
#endif
}


/**
 * @brief Match an input against a Regular Expression (@p regex) and convert the @p line to a float.
 *
 * @param line  The input to validate and parse.
 * @param regex The regex to use for validation.
 *
 * @return The float that is parsed from the input.
 *
 * @throw `std::invalid_argument` If no pattern can be matched in the string @p line.
 */
inline float parseAsFloat(const std::string& line, const std::regex& regex = NUMBER_REGEX)
{
    std::smatch match;
    if (std::regex_search(line, match, regex))
        return std::stof(match.str(1));
    else
        throw std::invalid_argument("Not a valid input. Must be a number or start with % or $");
}


#endif
