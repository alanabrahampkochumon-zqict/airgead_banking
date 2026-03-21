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
#include <string>
#include <sstream>

/**
 * @brief Outputs a @ref std::string with center alignment to the console.
 *
 * @param str       The string to print.
 * @param lineWidth The total width of the console output.
 */
inline void printCentered(const std::string& str, const int lineWidth)
{
    int totalInside = lineWidth - 2;
    int leftPadding = static_cast<int>(totalInside - str.length()) / 2;
    int rightPadding = static_cast<int>(totalInside - str.length() - leftPadding);

    std::cout << std::setfill(' ') << std::setw(leftPadding) << "" << str << std::setw(rightPadding) << "";
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


#endif
