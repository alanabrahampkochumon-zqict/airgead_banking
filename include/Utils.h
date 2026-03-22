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


#include "Config.h"

#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

/**
 * @brief Outputs a @ref std::string with center alignment to the console.
 *
 * @param t_str       The string to print.
 * @param t_lineWidth The total width of the console output.
 * @param t_fill      The fill to use for padding the left and right sides.
 */
inline void printCentered(const std::string& t_str, const int t_lineWidth, const char t_fill = ' ')
{
    int totalInside = t_lineWidth; // NOTE: Removed - 2
    int leftPadding = static_cast<int>(totalInside - t_str.length()) / 2;
    int rightPadding = static_cast<int>(totalInside - t_str.length() - leftPadding);

    std::cout << std::setfill(t_fill) << std::setw(leftPadding) << "" << t_str << std::setw(rightPadding) << "";
}


/**
 * @brief Outputs a table header to the screen.
 *
 * @param t_str       The string to print.
 * @param t_lineWidth The total width of the console output.
 */
inline void printTableHeader(const std::string& t_str, const int t_lineWidth)
{
    std::cout << std::setw(t_lineWidth);
    printCentered(t_str, t_lineWidth);
    std::cout << "\n" << std::setw(t_lineWidth) << std::setfill('=') << "" << "\n";
}


/**
 * @brief Formats an amount to a currency with 1/100th precision.
 *        Adds currency symbol.
 *
 * @param t_amount The amount to format.
 *
 * @return The formatted amount.
 */
inline std::string formatCurrency(float t_amount)
{
    std::stringstream data;
    data << CURRENCY_SYMBOL;
    data << std::setprecision(2);
    data << std::fixed;
    data << t_amount;

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
