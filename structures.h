/******************************************************
** File            :   structures.h
** Date            :   2022/7/20
** This File contains structures used in program
******************************************************/

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QDateTime>
#include <iostream>
#include <vector>

struct Request {

  QDate dateOfRequest; // the date that request applied
  int hours;           // number of hours applied

  long long int amountOfMoney;
};

struct EmployeeStructure {
  std::string name;
  std::string lastName;
  std::string userName;
  std::string password;
  int userID;
  int birthDay;
  int birthMonth;
  int birthYear;
  long long int salary;

  int vacHours;
  int monthRequestForVacation;
  int yearRequestForVacation;

  int overTimeHours;
  int monthRequestForOverTimeWork;
  int yearRequestForOverTimeWork;
};

struct ClientStructure {
  std::string name;
  std::string lastName;
  std::string userName;
  std::string password;
  int birthDay;
  int birthMonth;
  int birthYear;
  long int nationalCode;
  int sizeOfAccounts;
};

struct AccountStructure {
  long long int accountNumber;
  int openingDay;
  int openingMonth;
  int openingYear;
  long long int balance;
  bool isActive;
  long int nationalCode;
};

#endif // STRUCTURES_H
