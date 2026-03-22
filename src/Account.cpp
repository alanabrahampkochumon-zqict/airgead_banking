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
#include <regex>

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

float Account::calculateYearlyInterest(float baseAmount, bool includeDeposit) const
{
    // Calculate the yearly interest
    float eoyInterest = 0.0f;
    for (int j = 0; j < 12; ++j)
    {
        const float interest = calculateMonthlyInterest(baseAmount, includeDeposit);

        // Increment base amount if `includeDeposit` is true
        baseAmount = includeDeposit ? baseAmount + m_anticipatedDeposit + interest : baseAmount;

        // Add the current month's interest to the yearly total
        eoyInterest += interest;
    }

    return eoyInterest;
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
        // Calculate the yearly interest
        const float eoyInterest = calculateYearlyInterest(baseAmount, includeDeposit);

        // Calculate the deposit based on the includeDeposit flag
        const float deposit = (includeDeposit ? m_anticipatedDeposit * 12 : 0);

        // Calculate end of year amount
        const float totalAmount = baseAmount + eoyInterest + deposit;

        // Print the amount
        printRows({ std::to_string(i), formatCurrency(totalAmount), formatCurrency(eoyInterest) });

        // Update the base amount to be the new CI deposit
        baseAmount = totalAmount;
    }
    // TODO: Revert back to black-white color
    std::cout << "\n";
}

float parseAsFloat(std::string line)
{
    std::smatch match;
    std::regex pattern("[$,%]{0,1}(\\d+.{0,1}\\d*)"); // Matches $1.00, 1, 1.00, %5, %5.0, 
    if (std::regex_search(line, match, pattern))
    {
        std::string result = match.str(1);
        return std::stof(result);
    }
    else
        throw std::invalid_argument("Not a valid input. Must be a number or start with % or $");

}


Account Account::createAccount()
{
    //parseAsFloat("$1.0");
    //parseAsFloat("$1.00");
    //parseAsFloat("$1.2351234124");
    //parseAsFloat("1.0");
    //parseAsFloat("100");
    //parseAsFloat("%5");
    //parseAsFloat("5");
    std::cout << CONSOLE_COLOR; // Configures console to print in color of the config.

    std::cout << std::setw(2 * COLUMN_WIDTH) << std::setfill('*') << "" << "\n";
    printCentered(" Data Input ", 2 * COLUMN_WIDTH, '*');
    std::cout << "\n";

    constexpr int inputSize = 4; // The number of inputs.

    // Indices for the different data types.
    constexpr static unsigned int AMOUNT_INDEX = 0;
    constexpr static unsigned int DEPOSIT_INDEX = 1;
    constexpr static unsigned int INTEREST_INDEX = 2;
    constexpr static unsigned int YEAR_INDEX = 3;
    
    const std::string messages[inputSize] = { "Initial Investment Amount: ", "Monthly Deposit: ", "Annual Interest: ",
                                         "Number of years: " };

    float data[inputSize]; // Temporary storage getting data


    int i = 0;
    while (i < inputSize)
    {
        try
        {
            std::cout << messages[i];
            std::string rawBuffer;
            std::getline(std::cin, rawBuffer);
            data[i] = parseAsFloat(rawBuffer);
            if (data[i] < 1.0f)
                throw std::invalid_argument("Invalid input. Must be a positive number.");
            ++i;
        }
        catch (const std::ios_base::failure& _)
        {
            std::cout << "Invalid option! Try 1 - 4" << "\n";
            // Clears the input buffer.
            // Clears any errorneous input till newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << "\n";
            // Clears the input buffer.
            std::cin.clear();
            // Clears any errorneous input till newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "Press any key to continue...\n\n\n\n";
    std::cin.get(); // Pauses the execution then and there

    return Account(data[AMOUNT_INDEX], data[YEAR_INDEX], data[DEPOSIT_INDEX], data[INTEREST_INDEX]);
}