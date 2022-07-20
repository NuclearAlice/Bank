/******************************************************
** File            :   account.cpp
** Date            :   2022/7/20
** This File contains class Account methods
******************************************************/

#include "account.h"

/* constructor function : */
Account::Account() {}

/* this function gets a number as parameter
 * which is the amount we wana add to the balance */
void Account::addBalance(long long int balanceAdded) {

  /* add theamount to balance : */
  this->balance += balanceAdded;
}

/* this function gets an amount of money
 * and reduce that amount of money from balance */
bool Account::subtract(long long int balanceSubtracted) {

  /* make sure balance is more than this amount : */
  if ((this->balance) >= balanceSubtracted) {

    /* withdraw : */
    this->balance -= balanceSubtracted;

    /* return true as operation was successful : */
    return true;
  }

  /* else , balance is less than the amount,
   * operation is not possible : */
  return false;
}

/* this functions sets all the info got from struct into class object */
void Account::setStructure(AccountStructure structure) {

  this->balance = structure.balance;
  this->isActive = structure.isActive;
  this->openingDate.setDate(structure.openingYear, structure.openingMonth,
                            structure.openingDay);
  this->accountNumber = structure.accountNumber;
  this->ownerNationalCode = structure.nationalCode;
}

/* witre all account info into QString and return it */
QString Account::showInfoOfAccount() {

  QString info = ""; // holds the info of account

  /* set the info of this account : */
  info =
      "Account number :           " + QString::number(this->accountNumber) +
      "\n\nBalance :                       " + QString::number(this->balance) +
      "\n\nDate opened:                 " +
      QString::number(this->openingDate.year()) + " / " +
      QString::number(this->openingDate.month()) + " / " +
      QString::number(this->openingDate.day()) +
      "\n\nOwner national code :   " +
      QString::number(this->ownerNationalCode) +
      "\n\nStatus :                           ";
  if (isActive) {
    info += "active\n";
  } else {
    info += "not actice\n";
  }

  /* return the info stored in QString : */
  return info;
}

/* this function returns all info of account but owner national code */
QString Account::showInfoOfAccountWithoutOwnerNationalCode() {

  QString info = ""; // holds the info of account without national code

  /* set the info of this account but national code : */
  info = "Account number :         " + QString::number(this->accountNumber) +
         "\nBalance :                      " + QString::number(this->balance) +
         "\nDate opened:                " +
         QString::number(this->openingDate.year()) + " / " +
         QString::number(this->openingDate.month()) + " / " +
         QString::number(this->openingDate.day()) +
         "\nStatus :                        ";
  if (isActive) {
    info += "active\n";
  } else {
    info += "not actice\n";
  }

  /* return the info of account stored in QString : */
  return info;
}
