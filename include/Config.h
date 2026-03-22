#ifndef AIRGEAD_CONFIG
#define AIRGEAD_CONFIG
/**
 * @file Config.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 29, 2026
 *
 * @brief Configuration options for customizing Airgead UI and input validators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <regex>

static constexpr auto CONSOLE_COLOR = "\033[32m";      ///< Airgead's color configuration for console.
static constexpr auto CONSOLE_COLOR_RESET = "\033[0m"; ///< Default color configuration for console.
static constexpr int COLUMN_WIDTH = 24;                ///< Width of amount (money) column.
static constexpr int COLUMNS = 3;                      ///< Number of columns in the table.

static constexpr char CURRENCY_SYMBOL = '$'; ///< Currency symbol for formatting currencies.

/** @brief Regex for matching prices can be $1.00, 4.00, 1, or their negative counterparts. */
static const std::regex PRICE_REGEX("^[$]{0,1}(-{0,1}\\d+.{0,1}\\d*)$");
/** @brief Regex for matching percentages. Can be %5, %5.0, 5.0, or their negative counterparts. */
static const std::regex RATE_REGEX("^[%]{0,1}(-{0,1}\\d+.{0,1}\\d*)$");
/** @brief Regex for matching positive and negative integral and floating point numbers. */
static const std::regex NUMBER_REGEX("^(-{0,1}\\d+.{0,1}\\d*)$");

#endif