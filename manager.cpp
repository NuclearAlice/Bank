/******************************************************
** File            :   manager.cpp
** Date            :   2022/7/20
** This File contains Manager methods
******************************************************/

#include "manager.h"

Manager::Manager() {}

/*this function gets a number and a vector of clients as parameter , trys to
 * find the employee who that number is its user id, if any employee founds
 * return true*/
bool Manager::findAnEmployee(QString userIDInString,
                             std::vector<Employee> employees) {

  int userID; // holds integer of user id

  /*turn QString into integer:*/
  userID = userIDInString.toInt();

  /*in this loop we check all employee userID:*/
  for (int i = 0; i < (int)employees.size(); i++) {

    /*national code matches?*/
    if (employees[i].getUserId() == userID) {

      /*save index of employee for further operations:*/
      this->indexOfEmployee = i;

      /*return true as we found the employee:*/
      return true;
    }

    /*employee was not found return fales:*/
  }

  return false;
}

/*this function gets vector of employees and return info of one of them as
 * QString*/
QString Manager::showEmployeeInfo(std::vector<Employee> employee) {

  /*see if this is manager or no:*/
  if (this->indexOfEmployee == 0) {
    /*this is manager itself:*/
    return "This is you manager Alice\n" +
           employee[this->indexOfEmployee].showPersonalInfo();
  }

  /*this is not manager:*/
  return employee[this->indexOfEmployee].showPersonalInfo();
}

void Manager::hireEmployee(std::vector<Employee> &employees, QString userId,
                           QString name, QString familyName, QString birthYear,
                           QString birthMonth, QString birthDay,
                           QString userName, QString password, QString salary) {
  Employee newEmployee; // holds our new employee

  /*set info of new employee:*/

  /*step 1: set user id:*/
  newEmployee.setUserID(userId.toInt());

  /*step 2: set name:*/
  newEmployee.setName(name);

  /*step 3: set last name:*/
  newEmployee.setLastName(familyName);

  /*step 4: set user id:*/
  newEmployee.setBirthDate(birthDay.toInt(), birthMonth.toInt(),
                           birthYear.toInt());

  /*step 5: set userName:*/
  newEmployee.setUserName(userName);

  /*step 6: set password:*/
  newEmployee.setPassword(password);

  /*step 7: set basic salary:*/
  newEmployee.setBasicSalaryReceived(salary.toLongLong());

  /*step 8: set final salary:*/
  newEmployee.salaryCalculation();

  /*step 9: push back this employee to bank::vector<employee>:*/
  employees.push_back(newEmployee);

  /*save the index:*/
  this->indexOfEmployee = employees.size() - 1;

  /*Employee hired!*/
}

/*this function deletes an employee in the vector of employee it got as
 * parameter*/
void Manager::deleteEmployee(std::vector<Employee> &employees) {

  /*delete the employee by the index we had stored in
   * manager::inedxOfEmployee:*/

  /*check if index belong to manager or no:*/
  if (this->indexOfEmployee == 0)

  {
    /*this is manager, so deleting operation is not posssible*/
  }

  /*this is not manager , delete it:*/
  else {

    employees.erase(employees.begin() + this->indexOfEmployee);

    /*employee deleted!*/
  }
}
