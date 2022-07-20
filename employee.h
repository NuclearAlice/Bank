/******************************************************
** File            :   employee.h
** Date            :   2022/7/20
** This File contains class Employee
******************************************************/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "client.h"
#include "person.h"
#include "structures.h"
#include <iostream>
#include <vector>

class Employee : public Person {
public:
  /* constructor function : */
  Employee();

  /* setter functions : */
  void setUserID(int userID) { this->userID = userID; }
  void setBasicSalaryReceived(long long int basicSalaryReceived) {
    this->basicSalaryReceived = basicSalaryReceived;
  }
  void setOperationNumberInMenu(int i) { this->operationNumberInMenu = i; }

  /* getter functions : */
  int getOperationNumberInMenu() { return operationNumberInMenu; }
  int getClientIndex() { return indexOfClient; }
  int getUserId() { return userID; }
  int getHours() { return hours; }
  long long int getBasicSalary() { return basicSalaryReceived; }
  Request getVacHours() { return vacationHours; }
  Request getOverTimeHour() { return overTimeHours; }

  /* set structure into class : */
  void setStructure(EmployeeStructure);

  /* show vacation hours per month : */
  QString showVacationHours();

  /* this function shows the result of increases vacation hours : */
  QString increaseVacationHour();

  /* confirm for increasing vacation hours : */
  QString confirmIncreaseVacationHour();

  /* check if salary become 0 after operation : */
  bool checkSalaryIncreasingVacHours(QString);

  /* check for maximum over time work : */
  bool checkOverTimeWorkIsFull();

  /* over time hours data : */
  QString OverTimeHourData();

  /* check the hours requested for over time work : */
  bool checkOverTimeHoursRequested(QString);

  /* checks the final salary : */
  void salaryCalculation();

  /* show details of getting overTime work : */
  QString increaseOverTimeWorkHour();

  /* confirm for increasing overtime work hours : */
  QString confirmIncreaseOverTimeWorkHour();

  /* show personal info : */
  QString showPersonalInfo();

  /* find client by national code : */
  bool findAClient(long int, std::vector<Client>);

  /* show info of client : */
  QString showClientInfo(std::vector<Client>);

  /* create account for a client : */
  void createAccountForClient(std::vector<Client> &, QString);

  /* create account for new client : */
  void createAccountForNewClient(std::vector<Client> &, QString, QString,
                                 QString, QString, QString, QString, QString,
                                 QString, QString);

  /* search for an account among all clients : */
  bool searchForAccount(std::vector<Client> &, QString);

  /* delete account : */
  int deleteAccount(std::vector<Client> &, QString);

private:
  int indexOfClient; // holds the index of a client

  int userID;

  long long int basicSalaryReceived; // basic salary

  long long int finalSalary; // final salary after deduction or adding operation

  Request vacationHours;

  Request overTimeHours;

  int hours; // holds the hours for further operatoin

  int operationNumberInMenu; // holds the number of operation in  employee menu
};

#endif // EMPLOYEE_H
