/******************************************************
** File            :   client.h
** Date            :   2022/7/20
** This File contains class Client
******************************************************/

#ifndef CLIENT_H
#define CLIENT_H

#include "account.h"
#include "person.h"
#include "structures.h"
#include <iostream>
#include <vector>

class Client : public Person {
public:
  /* costructor function : */
  Client();

  /* setter functions : */
  void setNationalCode(long int nationalCode) {
    this->nationalCode = nationalCode;
  }
  void setAccount(Account account) { this->userAccount.push_back(account); }
  void setIndex(int index) { this->index = index; }
  void setOperationNumberInMenu(int i) { this->operationNumberInMenu = i; }

  /* getter functions : */
  long int getNationalCode() { return nationalCode; }
  int getIndex() { return index; }
  int getOperationNumberInMenu() { return operationNumberInMenu; }
  int getSizeOfAccount() { return sizeOfAccounts; }
  Account getAccount() { return userAccount[index]; }
  Account getAccountByIndex(int i) { return userAccount[i]; }

  /* adding account function : */
  void addAccount(Account);

  /* clear all accounts : */
  void clearAccounts();

  /* delete account : */
  bool deleteAccount(long long int);

  /* serach for the index of the account by account number : */
  int findTheAccountOfTheClient(long long int);

  /* set structure into class : */
  void setStructure(ClientStructure);

  /* show account numbers : */
  QString showNumbersOfAccounts();

  /* show client info : */
  QString showClientInfo();

  /* show account info : */
  QString showAllAccountsInfo();

  /* add balance to account : */
  void addBalanceToAccount(QString);

  /* withdraw : */
  bool withdraw(QString);

private:
  long int nationalCode;

  std::vector<Account> userAccount;

  int sizeOfAccounts = 0;

  int index; // holds index of one account

  /* 1 : increase balance
   * 2 : withdraw */
  int operationNumberInMenu; // holds the number of operation in  client menu
};

#endif // CLIENT_H
