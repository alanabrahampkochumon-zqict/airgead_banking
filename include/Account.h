#ifndef AIRGEAD_ACCOUNT
#define AIRGEAD_ACCOUNT
/**
 * @file Account.h
 * @author Alan Abraham Puthenparambil Kochumon
 * @date Created on: March 15, 2026
 *
 * @brief Representation of an Airgead recurring account.
 */

#include "Config.h"


class Account
{
public:
    /**
     * @brief Initialize an account with a provided balance.
     *
     * @param balance            The initial balance to start the account with.
     * @param maturityPeriod     The maturity period of deposit.
     * @param anticipatedDeposit The anticipated deposit that user will make per month.
     * @param interest           The interest of the account in percentage (0 - 100)
     *
     * @throw std::invalid_argument If @p balance or @p anticipatedDeposit is negative or @p maturityPeriod or @p
     * interest is less than 1.
     */
    Account(float balance, int maturityPeriod, float anticipatedDeposit, int interest);


    /**
     * @brief Output the calculated maturity amount per year.
     *
     * @param includeDeposit An indicator whether to include monthly deposit in the calculation.
     *
     */
    void printInterestTable(bool includeDeposit = false) const;


private:
    float m_balance;            ///< Balance in the account.
    int m_maturityPeriod;       ///< Maturity period of the account in years.
    float m_anticipatedDeposit; ///< Deposit user promise to make on a monthly basis.
    int m_interest;             ///< Interest payout of the account in percentage (0-100).


    /**
     * @brief Calculate the monthly compound interest.
     *        Using: \f[
     *                   \text{Compound Interest} = (\text{Opening Amount} + \text{Deposit}) \cdot \frac{12}{100} \cdot
     *                   \text{Interest Rate}
     *               \f]
     *
     * @param baseAmount            The opening amount to use for calculating interest.
     * @param includeMonthlyDeposit A flag to indicate whether to include monthly deposit in calculation.
     * @return The interest payout.
     */
    float calculateMonthlyInterest(float baseAmount, bool includeMonthlyDeposit = false) const;

    float Account::calculateYearlyDeposit(bool includeDeposit) const;
};


#endif