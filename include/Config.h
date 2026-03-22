#ifndef AIRGEAD_CONFIG
#define AIRGEAD_CONFIG
/**
 * @file Config.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 29, 2026
 *
 * @brief Configuration options for customizing look and Airgead UI.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <regex>

static constexpr const char* CONSOLE_COLOR = "\033[32m";      ///< Airgead's color configuration for console.
static constexpr const char* CONSOLE_COLOR_RESET = "\033[0m"; ///< Default color configuration for console.
static constexpr int COLUMN_WIDTH = 24;                       ///< Width of amount (money) column.
static constexpr int COLUMNS = 3;                             ///< Number of columns in the table.

static constexpr char CURRENCY_SYMBOL = '$'; ///< Currency symbol for formatting currencies.

static const std::regex PRICE_REGEX("^[$]{0,1}(-{0,1}\\d+.{0,1}\\d*)$");
static const std::regex RATE_REGEX("^[%]{0,1}(-{0,1}\\d+.{0,1}\\d*)$");
static const std::regex NUMBER_REGEX("^(-{0,1}\\d+.{0,1}\\d*)$");

#endif