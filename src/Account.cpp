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
#include "Config.h"

#include "Utils.h"

#include <iostream>
#include <regex>
#include <vector>

Account::Account(const float t_balance, const int t_maturityPeriod, const float t_anticipatedDeposit, const float t_interest)
    : m_balance(t_balance),
      m_maturityPeriod(t_maturityPeriod),
      m_anticipatedDeposit(t_anticipatedDeposit),
      m_interest(t_interest)
{
    if (m_balance < 0.0f)
        throw std::invalid_argument("Account cannot be initialized with a negative t_balance.");
    if (m_maturityPeriod < 0)
        throw std::invalid_argument("Maturity period cannot be less than a year");
    if (m_anticipatedDeposit < 0.0)
        throw std::invalid_argument("Anticipated deposit needs to be greater than 0");
    if (m_interest < 1)
        throw std::invalid_argument("Interest needs to be at least 1%");
}

float Account::calculateMonthlyInterest(const float t_baseAmount, const bool t_includeMonthlyDeposit) const
{
    const float deposit = t_includeMonthlyDeposit ? m_anticipatedDeposit : 0.0f;
    return (t_baseAmount + deposit) * (static_cast<float>(m_interest) / 12.0f / 100.0f);
}


/**
 * @brief Output the content as a row.
 *
 * @param[in] t_rows             The row of data to print.
 * @param[in] t_includeSeparator A flag to whether print the separate.
 *                         Default false.
 */
static void printRows(const std::vector<std::string>& t_rows, const bool t_includeSeparator = false)
{
    for (const auto& row : t_rows)
        std::cout << std::setfill(' ') << std::setw(COLUMN_WIDTH) << row;

    // Outputs the separator ----
    if (t_includeSeparator)
    {
        std::cout << "\n"
                  << std::setw(COLUMN_WIDTH * t_rows.size()) << std::setfill('-') << ""
                  << "\n";
        std::cout << std::setfill(' ');
    }
    std::cout << "\n";
}


float Account::calculateYearlyInterest(float t_baseAmount, const bool t_includeDeposit) const
{
    // Calculate the yearly interest
    float eoyInterest = 0.0f;
    for (int j = 0; j < 12; ++j)
    {
        const float interest = calculateMonthlyInterest(t_baseAmount, t_includeDeposit);

        // Increment base amount if `t_includeDeposit` is true
        t_baseAmount = t_includeDeposit ? t_baseAmount + m_anticipatedDeposit + interest : t_baseAmount + interest;

        // Add the current month's interest to the yearly total
        eoyInterest += interest;
    }

    return eoyInterest;
}


void Account::printInterestTable(const bool t_includeDeposit) const
{
    std::cout << CONSOLE_COLOR; // Configures console to print in color of the config.

    // Prints the header based on whether to include the deposit.
    if (t_includeDeposit)
        printTableHeader("Balance and Interest with Additional Monthly Deposit", COLUMNS * COLUMN_WIDTH);
    else
        printTableHeader("Balance and Interest without Additional Monthly Deposit", COLUMNS * COLUMN_WIDTH);

    printRows({ "Year", "Year End Balance", "Year End Interest" }, true);


    float baseAmount = m_balance;
    for (int i = 0; i < m_maturityPeriod; ++i)
    {
        // Calculate the yearly interest
        const float eoyInterest = calculateYearlyInterest(baseAmount, t_includeDeposit);

        // Calculate the deposit based on the t_includeDeposit flag
        const float deposit = (t_includeDeposit ? m_anticipatedDeposit * 12 : 0);

        // Calculate end of year amount
        const float totalAmount = baseAmount + eoyInterest + deposit;

        // Print the amount
        printRows({ std::to_string(i + 1), formatCurrency(totalAmount), formatCurrency(eoyInterest) });

        // Update the base amount to be the new CI deposit
        baseAmount = totalAmount;
    }
    std::cout << CONSOLE_COLOR_RESET << "\n"; // Clears the console color.
}


Account Account::createAccount()
{

    std::cout << CONSOLE_COLOR; // Configures console to print in color of the config.
    
    // Prints the header
    std::cout << std::setw(2 * COLUMN_WIDTH) << std::setfill('*') << "" << "\n";
    printCentered(" Data Input ", 2 * COLUMN_WIDTH, '*');
    std::cout << "\n";

    constexpr int inputSize = 4; // The number of inputs.

    // Indices for the different data types.
    constexpr static unsigned int AMOUNT_INDEX = 0;
    constexpr static unsigned int DEPOSIT_INDEX = 1;
    constexpr static unsigned int INTEREST_INDEX = 2;
    constexpr static unsigned int YEAR_INDEX = 3;

    // List of prompts to show for each input.
    const std::string messages[inputSize] = { "Initial Investment Amount: ", "Monthly Deposit: ", "Annual Interest: ",
                                              "Number of Years: " };
    // Regexes to use for validating each input.
    const std::regex validationRegex[inputSize] = { PRICE_REGEX, PRICE_REGEX, RATE_REGEX, NUMBER_REGEX };

    float data[inputSize]; // Temporary storage for each input.

    int i = 0;
    while (i < inputSize)
    {
        try
        {
            std::cout << messages[i];
            std::string rawBuffer;
            // Gets the input.
            std::getline(std::cin, rawBuffer);
            // Validates and parses the input as a float.
            data[i] = parseAsFloat(rawBuffer, validationRegex[i]);
            if (data[i] < 0.0f)
                throw std::invalid_argument("Invalid input. Must be a positive number.");
            ++i;
        }
        catch (const std::exception& e)
        {
            // Prints the error.
            std::cout << e.what() << "\n";
            // Clears the input buffer.
            std::cin.clear();
        }
    }
    std::cout << CONSOLE_COLOR_RESET << "\n"; // Clears the console color.
    return Account(data[AMOUNT_INDEX], data[YEAR_INDEX], data[DEPOSIT_INDEX], data[INTEREST_INDEX]);
}