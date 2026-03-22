/**
 * @file Main.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 29, 2026
 *
 * @brief Main Entry point to the program.
 *
 */

#include "Account.h"
#include "Utils.h"


/**
 * @brief Main entry point to program.
 * @return Implicitly returns an exit code, provided by modern compilers.
 */
int main()
{
    const Account account = Account::createAccount();
    suspendInput();
    clearScreen();
    account.printInterestTable();
    account.printInterestTable(true);
}
