/******************************************************
** File            :   client.cpp
** Date            :   2022/7/20
** This File contains class Client methods
******************************************************/

#include "client.h"

/* constructor function : */
Client::Client() {}

/* this functions gets an account as parameter, adds this account to the list */
void Client::addAccount(Account addingAccount) {

  /* push back the new account : */
  this->userAccount.push_back(addingAccount);

  /* increase size of accounts : */
  this->sizeOfAccounts++;
}

/* this function clears all accounts of this client */
void Client::clearAccounts() {

  /* clear the vector : */
  this->userAccount.clear();

  /* set the size zero : */
  this->sizeOfAccounts = 0;
}

/* this function gets account number and delets the account */
bool Client::deleteAccount(long long int deletingAccount) {

  int indexOfTheAccountWanaAdd; // this variable holds the index of the account
                                // we wana delete

  /* get the index from find function and put it in indexOfTheAccountWanaAdd*/
  indexOfTheAccountWanaAdd = findTheAccountOfTheClient(deletingAccount);

  /* if find function returns -1
   * it means that it couldnt find the account
   * so the delete operation will be canceled by returning false*/
  if (indexOfTheAccountWanaAdd == -1) {
    return false;
  }

  /* if find function doesnt return -1 ,
   * then it found the account,
   * delete the account by index : */
  else {

    /* delete the account : */
    this->userAccount.erase(userAccount.begin() + indexOfTheAccountWanaAdd);

    /* reduce the size of our accounts : */
    this->sizeOfAccounts--;

    /* delete operation was successful,
     * return true :*/
    return true;
  }
}

/* this function gets an account number,
 * and return the index of that account in client::vector<account> */
int Client::findTheAccountOfTheClient(long long int numberOfTheAccount) {

  /* check among all accounts of this client : */
  for (int i = 0; i < this->sizeOfAccounts; i++) {

    /* check if account number matches : */
    if (this->userAccount[i].getAccountNumber() == numberOfTheAccount) {

      /* if matches ,
       * save index into client::index,
       * and return the index : */
      this->index = i;
      return i;
    }
  }
  /* if account is not founr return -1 : */
  return -1;
}

/* this functions sets all the info got from struct into class object */
void Client::setStructure(ClientStructure structure) {

  /* turn the structure into client : */

  this->setName(QString::fromStdString(structure.name));
  this->setLastName(QString::fromStdString(structure.lastName));
  this->setUserName(QString::fromStdString(structure.userName));
  this->setPassword(QString::fromStdString(structure.password));
  this->setBirthDate(structure.birthDay, structure.birthMonth,
                     structure.birthYear);
  this->nationalCode = structure.nationalCode;
  this->sizeOfAccounts = structure.sizeOfAccounts;
}

/* this function return client account numbers as QString */
QString Client::showNumbersOfAccounts() {

  QString accountNumbers; // holds the account numbers we want

  /* set the accountNumbers emplty ,
   * cause we want to use += for it ,
   * we have to make sure does not have garbage value : */
  accountNumbers = "";

  /* in this loop we get number of all accounts : */
  for (int i = 0; i < this->sizeOfAccounts; i++) {

    accountNumbers +=
        QString::number(i + 1) + ". " +
        QString::number(this->getAccountByIndex(i).getAccountNumber()) + "\n";
  }

  /* now that we have all numbers in QString :: accountnumber return it : */
  return accountNumbers;
}

/* this function return all client info is QString */
QString Client::showClientInfo() {

  QString info; // holds info of client

  /* set it empty : */
  info = "";

  /* set the info : */
  info = "Name :                                               " +
         this->getName() +
         "\nLast name :                                       " +
         this->getLastName() +
         "\nNational code :                                  " +
         QString::number(this->nationalCode) +
         "\nBirth date :                                       " +
         QString::number(this->getbirthDate().year()) + " / " +
         QString::number(this->getbirthDate().month()) + " / " +
         QString::number(this->getbirthDate().day()) +
         "\nNumber of accounts in this bank :   " +
         QString::number(this->sizeOfAccounts);

  /* return the info we stored in info : */
  return info;
}

/* this function returns all accounts info of the client : */
QString Client::showAllAccountsInfo() {

  QString info; // holds the info of accounts

  /* set it empty : */
  info = "";

  /* in this loop we set accounts info into variable "info" ,
   * each time one account will be added : */
  for (int i = 0; i < this->sizeOfAccounts; i++) {

    /* call for the function which return account info in QString
     *  but without owner national code : */
    info += QString::number(i + 1) + ".\n" +
            this->userAccount[i].showInfoOfAccountWithoutOwnerNationalCode() +
            "____________________________________\n";
  }

  /* return the info we stored in info : */
  return info;
}

/* this function gets a QString as the amount we wana add to account,
 * also we had stored the index of our account before in client::index ,
 * so we know which account we wana add balance to*/
void Client::addBalanceToAccount(QString addingNumber) {

  /* turn QString to long long int then do the rest : */
  long long int addingAmount = addingNumber.toLongLong();

  /* call for client::add balance for adding operation : */
  this->userAccount[index].addBalance(addingAmount);
}

/* this function get QString turns it to long long int
 * and call for function account ::withdraw ,
 * and return the boolean that indicate if operation was successful or no*/
bool Client::withdraw(QString reducingNumber) {

  /* turn QString to long long int then do the rest : */
  long long int withdrawAmount = reducingNumber.toLongLong();

  /* now call account :: subrtact to withraw , return the result,if true then
   * it was succesful ,if false,then there was not enough balance to withraw :
   */
  return {this->userAccount[index].subtract(withdrawAmount)};
}
