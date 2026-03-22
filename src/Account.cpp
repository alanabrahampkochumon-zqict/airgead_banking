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

float Account::calculateMonthlyInterest(float baseAmount, bool includeMonthlyDeposit) const
{
    const float deposit = includeMonthlyDeposit ? m_anticipatedDeposit : 0.0f;
    return (baseAmount + deposit) * (static_cast<float>(m_interest) / 12.0f / 100.0f);
}


/**
 * @brief Output the content as a row.
 *
 * @param rows             The row of data to print.
 * @param includeSeparator A flag to whether print the separate.
 *                         Default false.
 */
static void printRows(const std::vector<std::string>& rows, bool includeSeparator = false)
{
    for (const auto& row : rows)
        std::cout << std::setfill(' ') << std::setw(COLUMN_WIDTH) << row;

    // Outputs the separator ----
    if (includeSeparator)
    {
        std::cout << "\n"
                  << std::setw(COLUMN_WIDTH * rows.size()) << std::setfill('-') << ""
                  << "\n";
        std::cout << std::setfill(' ');
    }
    std::cout << "\n";
}

float Account::calculateYearlyDeposit(bool includeDeposit) const
{
    float baseAmount = m_balance;
    for (int i = 1; i < m_maturityPeriod; ++i)
    {
        // Calculate the yearly interest
        float eoyInterest = 0.0f;
        for (int j = 0; j < 12; ++j)
        {
           
            float interest = calculateMonthlyInterest(baseAmount,
                                                    includeDeposit);
        // Increment base amount if `includeDeposit` is true
            baseAmount = includeDeposit ? baseAmount + m_anticipatedDeposit + interest: baseAmount;
            eoyInterest += interest;
        }
        std::cout << eoyInterest << ", ";
    }
    std::cout << "\n";
    return baseAmount;
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
    calculateYearlyDeposit(baseAmount);''
    for (int i = 1; i < m_maturityPeriod; ++i)
    {
        // Calculate the yearly interest
        float eoyInterest = 0.0f;
        for (int j = 0; j < 12; ++j)
            eoyInterest += calculateMonthlyInterest(includeDeposit ? baseAmount + j * m_anticipatedDeposit : baseAmount,
                                                    includeDeposit);

        // Calculate the deposit based on the includeDeposit flag
        const float deposit = (includeDeposit ? m_anticipatedDeposit * 12 : 0);

        // Calculate end of year amount
        const float totalAmount = baseAmount + eoyInterest + deposit;
        // Print the amount
        printRows({ std::to_string(i), formatCurrency(totalAmount), formatCurrency(eoyInterest) });
        // Update the base amount to be the new CI deposit
        baseAmount = totalAmount;
    }
}