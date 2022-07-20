/******************************************************
** File            :   manager.h
** Date            :   2022/7/20
** This File contains class Manager
******************************************************/

#ifndef MANAGER_H
#define MANAGER_H
#include "employee.h"

class Manager : public Employee {
public:
  /*constructor function:*/
  Manager();

  /*getter functions:*/
  int getIndexOfEmployee() { return indexOfEmployee; }

  /*find employee by user id:*/
  bool findAnEmployee(QString, std::vector<Employee>);

  /*show info of an employee:*/
  QString showEmployeeInfo(std::vector<Employee>);

  /*hire employee:*/
  void hireEmployee(std::vector<Employee> &, QString, QString, QString, QString,
                    QString, QString, QString, QString, QString);

  /*fire employee:*/
  void deleteEmployee(std::vector<Employee> &);

private:
  int indexOfEmployee; // holds index of employee
};

#endif // MANAGER_H
