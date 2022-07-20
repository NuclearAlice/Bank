/******************************************************
** File            :   bank.h
** Date            :   2022/7/20
** This File contains class Bank
******************************************************/

#ifndef BANK_H
#define BANK_H

#include "client.h"
#include "employee.h"
#include "manager.h"
#include "structures.h"
#include <QDateTime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Bank {
public:
  /* constructor function : */
  Bank();

  /* setter functions : */
  void setUserName(QString userName) { this->userName = userName; }
  void setPassword(QString password) { this->password = password; }
  void setReportInfo(QString reportInfo) {
    /* turn QString to std::string then set into Bank::reportInfo : */
    this->reportInfo = reportInfo.toStdString();
  }

  /* getter functions : */
  QString getUserName() { return userName; }
  QString getPassword() { return password; }
  Client getClient() { return clients[index]; }
  Client &getClientByIndex(int i) { return clients[i]; }
  Client &getClientByReference() { return clients[index]; }
  Employee getEmployee() { return employees[index]; }
  Employee &getEmployeeByReference() { return employees[index]; }
  int getIndex() { return index; }
  std::vector<Client> &getVectorOfClients() { return clients; }
  std::vector<Employee> &getVectorOfEmployee() { return employees; }
  Manager &getManagerByReference() { return manager; }

  /* set data from files functions : */
  bool setManagerDataFromFile();
  bool setClientsDataFromFile();
  bool setEmployeeDataFromFile();

  /* search for userNames : */
  bool searchForClientUserNamesAndPasswords();
  bool searchForManagerUserNamesAndPasswords();
  bool searchForEmployeeUserNamesAndPasswords();
  bool searchForPasswordAndUserName(QString, QString);

  /* these functions will record all actions into report file : */
  std::string timeRecorder();
  std::string dateRecorder();
  bool recordClientLogin();
  bool recordClientIncreasBalance();
  bool recordClientWithdrawBalance();
  bool recordEmployeeLeaveRequest();
  bool recordEmployeeLogin();
  bool recordEmployeeWorkTimeRequest();
  bool recordEmployeeCreateAccount();
  bool recordEmployeeDeteteAccount();
  bool recordManagerHireEmployee();
  bool recordManagerFireEmployee();

  /* 1 : client login
   * 2 : increase balance for client
   * 3 : withdraw for client
   * 4 : leave request for employee
   * 5 : employee login
   * 6 : over time work request
   * 7 : account created
   * 8 : delete account
   * 9 : hire employee
   * 10 : fire employee*/
  bool record(int);

  /* check if a QString is number or not : */
  bool checkNumber(QString);

  /* gets account number and return boolean if number is valid or not : */
  bool checkForValidAccountNumber(QString);

  /* return the account info which we had store its position before
   * in order to print info on screen : */
  QString getAccountInfo();

  /* find client by national code : */
  bool findClientByNationalCode(QString);

  /* save functions : */
  void save();
  void saveManager();
  void saveEmployee();
  void saveClient();

private:
  std::vector<Client> clients; // this vector holds clients

  std::vector<Employee> employees; // this vector hold employees of the bank

  Manager manager; // holds info of manager(which is Alice)

  Employee facilityOfficer; // no idea!

  QString branch; // name of branch

  int branchCode; // branch s' code

  QString userName; // this is used when someone logins,so we store user name to
                    // check for being valid later

  QString
      password; // this is also for login,so we could check if its valid or not

  int index; // holds the index of client or employee who login

  std::string reportInfo; // holds info needed for writing in report.txt
};

#endif // BANK_H
