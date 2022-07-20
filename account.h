/******************************************************
** File            :   account.h
** Date            :   2022/7/20
** This File contains class Account
******************************************************/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "structures.h"
#include <QDateTime>
#include <QString>
#include <iostream>

class Account {

public:
  /* construnctor function : */
  Account();

  /* setter functions : */
  void setNaionalCode(long long int ownerNationalCode) {
    this->ownerNationalCode = ownerNationalCode;
  }
  void setAccountNumber(long long int accountNumber) {
    this->accountNumber = accountNumber;
  }
  void setOpeningDate(QDate openingDate) { this->openingDate = openingDate; }
  void setBalance(long long int balance) { this->balance = balance; }
  void setActive(bool isActive) { this->isActive = isActive; }

  /* getter functions : */
  long long int getAccountNumber() { return accountNumber; }
  long long int getAccountBalance() { return balance; }
  bool getIsActive() { return isActive; }
  QDate getOpeningDate() { return openingDate; }
  bool getIsActice() { return isActive; }

  /* adds to balance : */
  void addBalance(long long int);

  /* withdraw : */
  bool subtract(long long int);

  /* set structure into class : */
  void setStructure(AccountStructure);

  /* show info of account : */
  QString showInfoOfAccount();

  /* show info of account with out owner national code : */
  QString showInfoOfAccountWithoutOwnerNationalCode();

private:
  long long int accountNumber;
  long long int ownerNationalCode;
  QDate openingDate;
  long long int balance;
  bool isActive;
};

#endif // ACCOUNT_H
