/******************************************************
** File            :   bank.cpp
** Date            :   2022/7/20
** This File contains class Bank methods
******************************************************/

#include "bank.h"

/* constructor function : */
Bank::Bank() {}

/* this functions will get manager data from its file,
 * if there wont be any problem with that,
 * returns true and if could not open file,
 * it will return false and the program wont even open */
bool Bank::setManagerDataFromFile() {

  EmployeeStructure
      managerDataGotFromFile; // holds the manager info read from file

  /* open file : */
  std::ifstream fin("/home/alice/code/HomeWork4/HomeWork/Alice.txt",
                    std::ios::in);

  /* read manager from file,
   * set it in a structure,
   * turn the structure to manager object in bank*/
  if (fin) {

    managerDataGotFromFile.userName = "Alice";

    fin >> managerDataGotFromFile.password;
    fin >> managerDataGotFromFile.name;
    fin >> managerDataGotFromFile.lastName;
    fin >> managerDataGotFromFile.userID;
    fin >> managerDataGotFromFile.birthDay;
    fin >> managerDataGotFromFile.birthMonth;
    fin >> managerDataGotFromFile.birthYear;
    fin >> managerDataGotFromFile.salary;
    fin >> managerDataGotFromFile.vacHours;
    fin >> managerDataGotFromFile.monthRequestForVacation;
    fin >> managerDataGotFromFile.yearRequestForVacation;
    fin >> managerDataGotFromFile.overTimeHours;
    fin >> managerDataGotFromFile.monthRequestForOverTimeWork;
    fin >> managerDataGotFromFile.yearRequestForOverTimeWork;
    manager.setStructure(managerDataGotFromFile);

    fin.close();

    /*calculate the final salary:*/
    this->manager.salaryCalculation();

    return true;
  }

  /* could not open file : */
  return false;
}

/* this function will read information of the employees from file,
 * save it to Bank::employees */
bool Bank::setEmployeeDataFromFile() {

  EmployeeStructure employeesReadFromFile; // structure used to read file

  Employee OneEmployeeReadInLoop; // employee used to get each employee data
                                  // from structure

  /* first of all , push back manager info to bank::employees : */
  this->employees.push_back(this->manager);

  /* now after manager alice,
   * we set info of other employees : */

  /* using an structure to read file then put it into an object of Employee
   * then push back all of these employees : */

  /* open employee file : */
  std::fstream fin("/home/alice/code/HomeWork4/HomeWork/Employee.txt",
                   std::ios::in);
  if (!fin) {
    /* if file did not open,
     * return false as setting employee info has failed : */
    return false;
  }

  /* file is open , start reading process : */
  while (fin) {
    fin >> employeesReadFromFile.userName;
    fin >> employeesReadFromFile.password;
    fin >> employeesReadFromFile.name;
    fin >> employeesReadFromFile.lastName;
    fin >> employeesReadFromFile.userID;
    fin >> employeesReadFromFile.birthDay;
    fin >> employeesReadFromFile.birthMonth;
    fin >> employeesReadFromFile.birthYear;
    fin >> employeesReadFromFile.salary;
    fin >> employeesReadFromFile.vacHours;
    fin >> employeesReadFromFile.monthRequestForVacation;
    fin >> employeesReadFromFile.yearRequestForVacation;
    fin >> employeesReadFromFile.overTimeHours;
    fin >> employeesReadFromFile.monthRequestForOverTimeWork;
    fin >> employeesReadFromFile.yearRequestForOverTimeWork;

    /* turn structure to class object : */
    OneEmployeeReadInLoop.setStructure(employeesReadFromFile);

    /* calculate the final salary : */
    OneEmployeeReadInLoop.salaryCalculation();

    /* set the employee into bank::vector<employee> : */
    this->employees.push_back(OneEmployeeReadInLoop);
  }
  this->employees.pop_back();

  /* reading compeleted,
   * close file : */
  fin.close();

  /* return true as process was successful : */
  return true;
}

/* this function will read information of the clients,
 * save it to Bank::clients */
bool Bank::setClientsDataFromFile() {

  /* using an structure to read file,
   * put it into an object of Client,
   * then push back all of these Clients */

  ClientStructure clientsReadFromFile; // structure used to read file

  Client oneClientReadInLoop; // client used to get each client data
                              // from structure

  AccountStructure accountReadFromFile; // structure used to read file

  Account
      oneAccountReadInLoop; // class object which holds value got from structure

  std::fstream fin("/home/alice/code/HomeWork4/HomeWork/Clients.txt",
                   std::ios::in);
  if (!fin) {
    return false;
  }
  while (fin) {
    fin >> clientsReadFromFile.userName;
    fin >> clientsReadFromFile.password;
    fin >> clientsReadFromFile.name;
    fin >> clientsReadFromFile.lastName;
    fin >> clientsReadFromFile.nationalCode;
    fin >> clientsReadFromFile.birthDay;
    fin >> clientsReadFromFile.birthMonth;
    fin >> clientsReadFromFile.birthYear;
    fin >> clientsReadFromFile.sizeOfAccounts;

    /* turn struct to class object : */
    oneClientReadInLoop.setStructure(clientsReadFromFile);

    /* read accounts info : */
    for (int i = 0; i < clientsReadFromFile.sizeOfAccounts; i++) {
      fin >> accountReadFromFile.accountNumber;
      fin >> accountReadFromFile.openingDay;
      fin >> accountReadFromFile.openingMonth;
      fin >> accountReadFromFile.openingYear;
      fin >> accountReadFromFile.balance;
      fin >> accountReadFromFile.isActive;

      /* turn struct to class object : */
      oneAccountReadInLoop.setStructure(accountReadFromFile);

      oneAccountReadInLoop.setNaionalCode(clientsReadFromFile.nationalCode);
      oneClientReadInLoop.setAccount(oneAccountReadInLoop);
    }

    /* push back the client to bank::vactor<clients> : */
    this->clients.push_back(oneClientReadInLoop);

    /* clear the accounts of this temporaty client,
     * which in each time of this loop new account will be added to it
     * and the last account are the garbage accounts it holds : */
    oneClientReadInLoop.clearAccounts();
  }

  /* reading bug,
   * gets one client more,
   * remove this client : */
  this->clients.pop_back();

  /* close file : */
  fin.close();

  /* reading file was successful,
   * return true : */
  return true;
}

/* this funtion checks if the user name and password of client is correct or no*/
bool Bank::searchForClientUserNamesAndPasswords() {

  /*in this loop ,we check all clients userName and passwords:*/
  for (int i = 0; i < (int)this->clients.size(); i++) {

    /*check if userName mathes:*/
    if (this->clients[i].getUserName() == this->userName) {

      /*if userName matches check is password matches:*/
      if (this->clients[i].getPassword() == this->password) {

        /*now that both userName and passwords mathes and client is found, first
         * save client index into Bank::index for further operations and then
         * return true ans userName ans password are correct:*/
        this->index = i;
        return true;
      }
    }
  }
  return false;
}

/*this function checks if password and userName belong to an employee*/
bool Bank::searchForEmployeeUserNamesAndPasswords() {

  /*check info of all employees from bank::vector<employee> in a loop :*/
  for (int i = 0; i < (int)this->employees.size(); i++) {

    /*checks if among all employees userName mathes:*/
    if (employees[i].getUserName() == this->userName) {

      /*userName mathches,check for password:*/
      if (employees[i].getPassword() == this->password) {

        /*if both userName and password matches,then employee found, save
         * employee index into Bank::index and then return true:*/
        this->index = i;
        return true;
      }
    }
  }

  /*if userName and password was not found in loop,then userName and password is
   * invalid , so return false:*/
  return false;
}

/*this function checks if there is userName and password among clients or
 * employees same as the one we have in parameter*/
bool Bank::searchForPasswordAndUserName(QString userName, QString password) {

  /*search among clients:*/
  for (int i = 0; i < (int)this->clients.size(); i++) {

    if (this->clients[i].getUserName() == userName) {

      if (this->clients[i].getPassword() == password) {

        /*found a client with such userName and password:*/
        return true;
      }
    }
  }

  /*search among employees:*/
  for (int i = 0; i < (int)this->employees.size(); i++) {

    if (this->employees[i].getUserName() == userName) {

      if (this->employees[i].getPassword() == password) {

        /*found an employee with such userName and password:*/
        return true;
      }
    }
  }

  return false;
}

std::string Bank::dateRecorder() {
  QDate date = QDate::currentDate(); // finding current date
  /*turn that date into string*/
  std::string currentDate = std::to_string(date.year()) + " / " +
                            std::to_string(date.month()) + " / " +
                            std::to_string(date.day());

  /*return date string*/
  return currentDate;
}

std::string Bank::timeRecorder() {
  QTime time = QTime::currentTime(); // finding current time
  /*turn that time into string*/
  std::string currentTime = std::to_string(time.hour()) + " : " +
                            std::to_string(time.minute()) + " : " +
                            std::to_string(time.second());

  /*return time string*/
  return currentTime;
}
bool Bank::recordClientLogin() {

  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);
  if (fout) {
    fout << "Account with national code [ "
         << this->clients[index].getNationalCode() << " ] login in date "
         << this->dateRecorder() << " time " << this->timeRecorder()
         << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records time and date we increased balance of an account*/
bool Bank::recordClientIncreasBalance() {
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);
  if (fout) {
    fout << "Account with national code [ "
         << this->clients[index].getNationalCode()
         << " ] increase account balance with amount " << this->reportInfo
         << " in date " << this->dateRecorder() << " time "
         << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records withdraw operation into report.txt file*/
bool Bank::recordClientWithdrawBalance() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Account with national code [ "
         << this->clients[index].getNationalCode()
         << " ] withdraw account balance with amount " << this->reportInfo
         << " in date " << this->dateRecorder() << " time "
         << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records leave request into report.txt file*/
bool Bank::recordEmployeeLeaveRequest() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Employee with user id [ " << this->employees[index].getUserId()
         << " ] gets [ " << this->employees[index].getHours()
         << " ] hours rest for this month in date " << this->dateRecorder()
         << " time " << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records employee login into report.txt file*/
bool Bank::recordEmployeeLogin() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Employee with user id [ " << this->employees[index].getUserId()
         << " ] login in date " << this->dateRecorder() << " time "
         << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records overTime work request into report.txt file*/
bool Bank::recordEmployeeWorkTimeRequest() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Employee with user id [ " << this->employees[index].getUserId()
         << " ] gets [ " << this->employees[index].getHours()
         << " ] hours overtime work for this month in date "
         << this->dateRecorder() << " time " << this->timeRecorder()
         << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records create account operation into report.txt file*/
bool Bank::recordEmployeeCreateAccount() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Account with national code [ "
         << this->clients[employees[index].getClientIndex()].getNationalCode()
         << " ] is created in date " << this->dateRecorder() << " time "
         << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records delete account operation into report.txt file*/
bool Bank::recordEmployeeDeteteAccount() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Account with national code [ "
         << this->clients[employees[index].getClientIndex()].getNationalCode()
         << " ] is deleted in date " << this->dateRecorder() << " time "
         << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records hire employee operation into report.txt file*/
bool Bank::recordManagerHireEmployee() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Employee with user id [ "
         << this->employees[this->manager.getIndexOfEmployee()].getUserId()
         << " ] is hired in date " << this->dateRecorder() << " time "
         << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function records fire employee operation into report.txt file*/
bool Bank::recordManagerFireEmployee() {

  /*opening the report.txt file*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/report.txt",
                     std::ios::app);

  /*if open ,do the recording */
  if (fout) {
    fout << "Employee with user id [ "
         << this->employees[this->manager.getIndexOfEmployee()].getUserId()
         << " ] is fired in date " << this->dateRecorder() << " time "
         << this->timeRecorder() << std::endl;
    fout.close();
    return true;
  }
  return false;
}

/*this function is for report.txt file ,which record all actions such as logins
 * or other operations,it takes an integer which indicate the type of action
 * that has happend*/
bool Bank::record(int typeOfRecord) {

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

  switch (typeOfRecord) {

  case 1:
    /*record time if client login*/
    if (!recordClientLogin()) {
      return false;
    }
    break;

  case 2:
    /*record time if adding balance to an account*/
    if (!recordClientIncreasBalance()) {
      return false;
    }
    break;

  case 3:
    /*record time if withdraw has happend*/
    if (!recordClientWithdrawBalance()) {
      return false;
    }
    break;

  case 4:
    /*record time if leave request has happend*/
    if (!recordEmployeeLeaveRequest()) {
      return false;
    }
    break;

  case 5:
    /*record time if employee login*/
    if (!recordEmployeeLogin()) {
      return false;
    }
    break;

  case 6:
    /*record time if over time request has happend*/
    if (!recordEmployeeWorkTimeRequest()) {
      return false;
    }
    break;

  case 7:
    /*record time if create account*/
    if (!recordEmployeeCreateAccount()) {
      return false;
    }
    break;

  case 8:
    /*record time if delete account*/
    if (!recordEmployeeDeteteAccount()) {
      return false;
    }
    break;

  case 9:
    /*record time if delete account*/
    if (!recordManagerHireEmployee()) {
      return false;
    }
    break;

  case 10:
    /*record time if delete account*/
    if (!recordManagerFireEmployee()) {
      return false;
    }
    break;

  default:
    return false;
    break;
  }
  return true;
}

/*this function gets QString,checks all of its characters,see if its all numbers
 * or not,cause as an example we are looking for account number and if input has
 * some other charecters except numbers ,then its not valid,this function is
 * used for error handlings*/
bool Bank::checkNumber(QString num) {
  for (int i = 0; i < num.size(); i++) {
    if (!(num[i] == '1' || num[i] == '2' || num[i] == '3' || num[i] == '4' ||
          num[i] == '5' || num[i] == '6' || num[i] == '7' || num[i] == '8' ||
          num[i] == '9' || num[i] == '0')) {
      /*if found charecter which is not a number returns false,
       * otherwise return true*/
      return false;
    }
  }
  return true;
}

/*this function gives the info of the client account, it returns QString so we
 * can print it on screen*/
QString Bank::getAccountInfo() {
  Client tmpClient; // temporary variable which is used for the client we are
                    // talking about

  QString info; // holds info of account

  /*setting the client we are talking about into out tmp client*/
  tmpClient = clients[index];

  /*get the account info and return it: first goes for the selected account
   * which we had store its index in client::index before, then use a get
   * function to get this index,use the index to specify which account we are
   * talking about ,then call the show info function of the account,which
   * returns string,so we turn string into QString and return this QString*/
  info =
      (tmpClient.getAccountByIndex(tmpClient.getIndex())).showInfoOfAccount();

  return info;
}

/*this function get QString, turns it to long long integer, this number is the
 number of the account we are looking for, then if finds the index of account
 , returns it if not returns -1*/
bool Bank::checkForValidAccountNumber(QString num) {
  int indexOfAccount; // holds the index of ccount in client::vector<account>
  long long int
      numberOfAccount; // this temporary variable holds the number of account

  /*settting number of account into the variable*/
  numberOfAccount = num.toLongLong();

  /*find the index of account and save it into tmp variable*/
  indexOfAccount = clients[index].findTheAccountOfTheClient(numberOfAccount);

  /*check if the index is not -1 then its valid,return true if valid*/
  if (indexOfAccount != -1) {

    /*saving index of account for futher operations into client::index*/
    clients[index].setIndex(indexOfAccount);
    return true;
  }

  /*now return false if index is -1*/
  return false;
}

/*this function gets national code of a client and look for it, if found, return
 * true*/
bool Bank::findClientByNationalCode(QString codeInString) {

  long int nationalCode; // hode the value of national code in integer

  /*turn QString to long int and set it into int::nationalCode:*/
  nationalCode = codeInString.toLong();

  /*call for employee function:*/
  if (this->employees[index].findAClient(nationalCode, this->clients)) {

    /*client found , return true:*/
    return true;
  }

  /*client was not found , return false:*/
  return false;
}

/*this function saves manager info into Alice.txt*/
void Bank::saveManager() {

  /*open file:*/
  std::ofstream fout("/home/alice/code/HomeWork4/HomeWork/Alice.txt",
                     std::ios::trunc);
  if (fout) {

    fout << manager.getPassword().toStdString() << std::endl;
    fout << manager.getName().toStdString() << std::endl;
    fout << manager.getLastName().toStdString() << std::endl;
    fout << manager.getUserId() << std::endl;
    fout << manager.getbirthDate().day() << std::endl;
    fout << manager.getbirthDate().month() << std::endl;
    fout << manager.getbirthDate().year() << std::endl;
    fout << manager.getBasicSalary() << std::endl;
    fout << manager.getVacHours().hours << std::endl;
    fout << manager.getVacHours().dateOfRequest.month() << std::endl;
    fout << manager.getVacHours().dateOfRequest.year() << std::endl;
    fout << manager.getOverTimeHour().hours << std::endl;
    fout << manager.getOverTimeHour().dateOfRequest.month() << std::endl;
    fout << manager.getOverTimeHour().dateOfRequest.year() << std::endl;

    fout.close();
  }
}

/*this function saves clients info into Clients.txt*/
void Bank::saveClient() {

  /*opean file:*/
  std::ofstream fout(
      "/home/alice/code/HomeWork4/HomeWork/Clients.txt",
      std::ios::trunc);
  if (fout) {
    for (int i = 0; i < (int)clients.size(); i++) {

      fout << clients[i].getUserName().toStdString() << std::endl;
      fout << clients[i].getPassword().toStdString() << std::endl;
      fout << clients[i].getName().toStdString() << std::endl;
      fout << clients[i].getLastName().toStdString() << std::endl;
      fout << clients[i].getNationalCode() << std::endl;
      fout << clients[i].getbirthDate().day() << std::endl;
      fout << clients[i].getbirthDate().month() << std::endl;
      fout << clients[i].getbirthDate().year() << std::endl;
      fout << clients[i].getSizeOfAccount() << std::endl;
      for (int j = 0; j < clients[i].getSizeOfAccount(); j++) {

        fout << clients[i].getAccountByIndex(j).getAccountNumber() << std::endl;
        fout << clients[i].getAccountByIndex(j).getOpeningDate().day()
             << std::endl;
        fout << clients[i].getAccountByIndex(j).getOpeningDate().month()
             << std::endl;
        fout << clients[i].getAccountByIndex(j).getOpeningDate().year()
             << std::endl;
        fout << clients[i].getAccountByIndex(j).getAccountBalance()
             << std::endl;
        fout << clients[i].getAccountByIndex(j).getIsActive() << std::endl;
      }
    }

    fout.close();
  }
}

/*this function saves employee info into Clients.txt*/
void Bank::saveEmployee() {

  /*opean file:*/
  std::ofstream fout(
      "/home/alice/code/HomeWork4/HomeWork/Employee.txt",
      std::ios::trunc);
  if (fout) {
    for (int i = 1; i < (int)employees.size(); i++) {

      fout << employees[i].getUserName().toStdString() << std::endl;
      fout << employees[i].getPassword().toStdString() << std::endl;
      fout << employees[i].getName().toStdString() << std::endl;
      fout << employees[i].getLastName().toStdString() << std::endl;
      fout << employees[i].getUserId() << std::endl;
      fout << employees[i].getbirthDate().day() << std::endl;
      fout << employees[i].getbirthDate().month() << std::endl;
      fout << employees[i].getbirthDate().year() << std::endl;
      fout << employees[i].getBasicSalary() << std::endl;
      fout << employees[i].getVacHours().hours << std::endl;
      fout << employees[i].getVacHours().dateOfRequest.month() << std::endl;
      fout << employees[i].getVacHours().dateOfRequest.year() << std::endl;
      fout << employees[i].getOverTimeHour().hours << std::endl;
      fout << employees[i].getOverTimeHour().dateOfRequest.month() << std::endl;
      fout << employees[i].getOverTimeHour().dateOfRequest.year() << std::endl;
    }

    fout.close();
  }
}

/*this function saves all bank ifo in files before closing program:*/
void Bank::save() {

  /*save manager into Alice.txt:*/
  saveManager();

  /*save clients:*/
  saveClient();

  /*save Employees:*/
  saveEmployee();
}
