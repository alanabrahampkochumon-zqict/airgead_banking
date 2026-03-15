/**
 * @file Account.cpp
 * @author Alan Abraham Puthenparambil Kochumon
 * @date Created on: March 29, 2026
 *
 * @brief Account implementation.
 *		  This file provide implementation for the member functions defined in @ref Account.h
 *
 */

#include "Account.h"

#include "Utils.h"

#include <iostream>
#include <vector>

Account::Account(float balance, int maturityPeriod, float anticipatedDeposit, int interest)
    : m_balance(balance),
      m_maturityPeriod(maturityPeriod),
      m_anticipatedDeposit(anticipatedDeposit),
      m_interest(interest)
{
    if (m_balance < 0.0f)
        throw std::invalid_argument("Account cannot be initialized with a negative balance.");
    if (m_maturityPeriod < 0)
        throw std::invalid_argument("Maturity period cannot be less than a year");
    if (m_anticipatedDeposit < 0.0)
        throw std::invalid_argument("Anticipated deposit needs to be greater than 0");
    if (m_interest < 1)
        throw std::invalid_argument("Interest needs to be at least 1%");
}

float Account::calculateInterest(float baseAmount) const
{
    return (baseAmount + m_anticipatedDeposit) * ((m_interest) * 12.0f / 100.0f);
}


/**
 * @brief Outputs the content as a row.
 *
 * @param rows: The row of data to print.
 * @param includeSeparator: A flag to whether print the separate.
 *        Default false.
 */
static void printRows(const std::vector<std::string>& rows, bool includeSeparator = false)
{
    for (const auto& row : rows)
        std::cout << std::setw(COLUMN_WIDTH) << row;

    // Outputs the separator ----
    if (includeSeparator)
        std::cout << std::setw(COLUMN_WIDTH * rows.size()) << std::setfill('-') << ""
                  << "\n";
}


void Account::printInterestTable(bool includeDeposit) const
{
    std::cout << CONSOLE_COLOR; // Configures console to print in color of the config.

    // Prints the header based on whether to include the deposit.
    if (includeDeposit)
        printTableHeader("Balance and Interest Without Additional Monthly Deposit", COLUMNS * COLUMN_WIDTH);
    else
        printTableHeader("Balance and Interest With Additional Monthly Deposit", COLUMNS * COLUMN_WIDTH);

    printRows({ "Year", "Year End Balance", "Year End Interest" }, true);

    float baseAmount = m_balance;
    for (int i = 1; i < m_maturityPeriod; ++i)
    {
        const float interestPayout = calculateInterest(baseAmount);
        const float totalAmount = baseAmount + interestPayout;
        printRows(i, interestPayout, totalAmount);        
    }
}