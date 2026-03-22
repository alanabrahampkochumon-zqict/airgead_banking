/**
 * @file Main.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 29, 2026
 *
 * @brief Main Entry point of the program.
 * 
 */

#include "Account.h"

int main()
{
    const Account account = Account::createAccount();
    account.printInterestTable();
    account.printInterestTable(true);
    //Account account1(1, 10, .0, 5);
    //Account account2(50.0, 25, 1.0, 15);
    //account1.printInterestTable();
    //account1.printInterestTable(true);
    //account2.printInterestTable();
}

