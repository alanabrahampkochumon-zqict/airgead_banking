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
     * @brief Initializes an account with no balance.
     */
    Account();

    /**
     * @brief Initialize an account with a provided balance.
     * 
     * @param balance Balance to start the account with.
     */
    Account(float balance);


    /**
     * @brief Output the calculated maturity amount per year.
     *
     * @param includeDeposit An indicator whether to include monthly deposit in the calculation
     *
     */
    void printInterestTable(bool includeDeposit = false);


private:
    float balance; ///< Balance in the account.
    int maturityPeriod; ///< Maturity period of the account in years.
    float anticipatedDeposit; ///< Deposit use promises to make on a monthly basis.
};


#endif