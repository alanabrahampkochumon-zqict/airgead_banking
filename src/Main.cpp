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
    Account account(5.0, 3, 1.0, 15);
    account.printInterestTable();
}

