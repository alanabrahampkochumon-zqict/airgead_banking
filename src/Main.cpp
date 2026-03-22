/**
 * @file Main.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 29, 2026
 *
 * @brief Main Entry point of the program.
 *
 */

#include "Account.h"
#include "Utils.h"


int main()
{
    const Account account = Account::createAccount();
    suspendInput();
    clearScreen();
    account.printInterestTable();
    account.printInterestTable(true);
}
