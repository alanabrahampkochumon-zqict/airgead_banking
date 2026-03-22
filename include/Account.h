#ifndef AIRGEAD_ACCOUNT
#define AIRGEAD_ACCOUNT
/**
 * @file Account.h
 * @author Alan Abraham Puthenparambil Kochumon
 * @date Created on: March 15, 2026
 *
 * @brief Representation of an Airgead recurring account.
 */

class Account
{
public:
    /**
     * @brief Creates an account taking input from the user.
     * @return The newly created account.
     */
    static Account createAccount();

    /**
     * @brief Output the calculated maturity amount per year.
     *
     * @param[in] t_includeDeposit An indicator whether to include monthly deposit in the calculation.
     *
     */
    void printInterestTable(bool t_includeDeposit = false) const;

private:
    float m_balance;            ///< Balance in the account.
    int m_maturityPeriod;       ///< Maturity period of the account in years.
    float m_anticipatedDeposit; ///< Deposit user promise to make on a monthly basis.
    float m_interest;             ///< Interest payout of the account in percentage (>0-100).


    /**
     * @brief Initialize an account with a provided balance.
     *
     * @param[in] t_balance            The initial balance to start the account with.
     * @param[in] t_maturityPeriod     The maturity period of deposit.
     * @param[in] t_anticipatedDeposit The anticipated deposit that user will make per month.
     * @param[in] t_interest           The interest of the account in percentage (0 - 100)
     *
     * @throw std::invalid_argument If @p balance or @p anticipatedDeposit is negative or @p maturityPeriod or @p
     * interest is less than 1.
     */
    Account(float t_balance, int t_maturityPeriod, float t_anticipatedDeposit, float t_interest);

    /**
     * @brief Calculate the monthly compound interest.
     *        Using: \f[
     *                   \text{Compound Interest} = (\text{Opening Amount} + \text{Deposit}) \cdot \frac{12}{100} \cdot
     *                   \text{Interest Rate}
     *               \f]
     *
     * @param[in] t_baseAmount            The opening amount to use for calculating interest.
     * @param[in] t_includeMonthlyDeposit A flag to indicate whether to include monthly deposit in calculation.
     *
     * @return The monthly interest payout.
     */
    float calculateMonthlyInterest(float t_baseAmount, bool t_includeMonthlyDeposit = false) const;

    /**
     * @brief Calculate the yearly compound interest payout.
     *
     * @param[in] t_baseAmount     The base amount to use for calculation.
     *                       This can be the starting yearly amount.
     * @param[in] t_includeDeposit A flag to indicate whether to include monthly deposit in calculation.
     *
     * @return The yearly interest payout.
     */
    float Account::calculateYearlyInterest(float t_baseAmount, bool t_includeDeposit) const;
};


#endif