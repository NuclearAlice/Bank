/******************************************************
** File            :   employee.cpp
** Date            :   2022/7/20
** This File contains class Employee methods
******************************************************/

#include "employee.h"

/* constructor function */
Employee::Employee() {}

/* this functions sets all the info got from struct into class object */
void Employee::setStructure(EmployeeStructure structure) {

  this->setName(QString::fromStdString(structure.name));
  this->setLastName(QString::fromStdString(structure.lastName));
  this->setUserName(QString::fromStdString(structure.userName));
  this->setPassword(QString::fromStdString(structure.password));
  this->userID = structure.userID;
  this->setBirthDate(structure.birthDay, structure.birthMonth,
                     structure.birthYear);
  this->basicSalaryReceived = structure.salary;
  this->vacationHours.hours = structure.vacHours;
  this->vacationHours.dateOfRequest.setDate(
      structure.yearRequestForVacation, structure.monthRequestForVacation, 1);
  this->overTimeHours.hours = structure.overTimeHours;
  this->overTimeHours.dateOfRequest.setDate(
      structure.yearRequestForOverTimeWork,
      structure.monthRequestForOverTimeWork, 1);
}

/* this function calculates final salary : */
void Employee::salaryCalculation() {

  QDate today; // holds the todays date

  /* set todays date : */
  today = QDate::currentDate();

  /* check the requests : */

  /* vacation hours : */
  if (today.year() == this->vacationHours.dateOfRequest.year()) {
    if (today.month() == this->vacationHours.dateOfRequest.month()) {

      /* requsts are for this months */
    }

    /* if requests are not for this month set the hours 0 : */
    else {
      this->vacationHours.hours = 0;
    }
  }

  /* if requests are not for this year set the hours 0 : */
  else {
    this->vacationHours.hours = 0;
  }

  /* over time work hours : */
  if (today.year() == this->overTimeHours.dateOfRequest.year()) {
    if (today.month() == this->overTimeHours.dateOfRequest.month()) {

      /* requsts are for this months */

    }

    /* if requests are not for this month set the hours 0 : */
    else {
      this->overTimeHours.hours = 0;
    }
  }

  /* if requests are not for this year set the hours 0 : */
  else {
    this->overTimeHours.hours = 0;
  }

  /* set the amount of money for every hours : */
  /* for vacation hours if more than 15 : */
  if (this->vacationHours.hours > 15) {
    this->vacationHours.amountOfMoney =
        (this->vacationHours.hours - 15) * 100000;
  }
  /* else if was not more than 15, set it 0 : */
  else {
    this->vacationHours.amountOfMoney = 0;
  }

  /* for over time hour : */
  this->overTimeHours.amountOfMoney = this->overTimeHours.hours * 120000;

  this->finalSalary = this->basicSalaryReceived;
  this->finalSalary -= this->vacationHours.amountOfMoney;
  this->finalSalary += this->overTimeHours.amountOfMoney;
}

/* this function returns a QString
 * which is for vacation hour that has been requested ,
 * this QString contains info that shows how many hours we already have,
 * also how many hours can we request*/
QString Employee::showVacationHours() {

  QDate today; // holds todays' date

  QString vacHours = ""; // holds the info we wana return

  /* find current date : */
  today = QDate::currentDate();

  /* see if in this month any vacation hours has been requested or no : */
  if (today.year() == this->vacationHours.dateOfRequest.year()) {
    if (today.month() == this->vacationHours.dateOfRequest.month()) {

      /* make sure that hours in this month is not 0 : */
      if (vacationHours.hours != 0) {

        /* in this month , there 's been requests ,
         * so write vacation hours we already have into QString
         * and return vachours : */
        vacHours = "Vacation hours in this month : " +
                   QString::number(this->vacationHours.hours);

        /* check if hours are not more than 15, show the remaining hours : */
        if (this->vacationHours.hours < 15) {
          vacHours += "\nYou can request for " +
                      QString::number(15 - this->vacationHours.hours) +
                      " more hours";
        }
        return vacHours;
      }
    }
  }

  /* there been no vacation hours for this month as we found,
   * calculate the salary again,
   * also set the hours 0 which will be done in the function : */
  this->salaryCalculation();

  /* write the right messege : */
  vacHours = "Leave request for this month has not been registered yet \nYou "
             "can request for 15 hours with no salary deduction";

  return vacHours;
}

/* this checks 2 possible conditions,
 * first condition is that vacation hour will be less than 15 hours,
 * the other condition is when hours become more than 15 hours,
 * return the right messege as QString*/
QString Employee::increaseVacationHour() {

  /* we had stored the hours we wana add into Employee::hours */

  int finalVacationHours; // holds the final number of vacation hours after
                          // adding operation

  QString messege; // holds the final messege

  /* add hours we wana add to vacation hours
   * and put the value into tmp variable finalVacationHours : */
  finalVacationHours = this->hours + this->vacationHours.hours;

  /* check for the first condition that hours will be less than 15 : */
  if (finalVacationHours <= 15) {

    /* now that hours are less than 15,
     * write the how many vacation hours will be if confirm : */
    messege = "After this operation the vacation hours will be : " +
              QString::number(finalVacationHours) +
              "\nClick on Go button to confirm...";
  }

  /* check for the second condition that the hours will be more than 15 : */
  else {

    /* check if base hours was more than 15 before adding new hours : */
    if (this->vacationHours.hours >= 15) {

      /* how many hours more than 15?for each hour 100000$ will be reduced : */
      messege = "your vacation hour will be more than 15\nBe aware that salary "
                "will be reduced "
                "if confirm\nAfter getting " +
                QString::number(this->hours) +
                " hours vacation , salary will be : " +
                QString::number(this->finalSalary - ((this->hours) * 100000)) +
                "\nClick on Go button to confirm...";
    }

    /* if base hour was less than 15
     * and it will be more than 15 after the adding operation : */
    else {

      /* how many hours more than 15?for each hour 100000$ will be reduced : */
      messege = "your vacation hour will be more than 15\nBe aware that salary "
                "will be reduced "
                "if confirm\nAfter getting " +
                QString::number(this->hours) +
                " hours vacation , salary will be : " +
                QString::number(this->finalSalary -
                                ((finalVacationHours - 15) * 100000)) +
                "\nClick on Go button to confirm...";
    }
  }

  return messege;
}

/* if go button was clicked
 * then this function will be called
 * to confirm increasing vacation hours */
QString Employee::confirmIncreaseVacationHour() {

  QString result; // holds the result as QString to report

  /* we had stored the hours we wana add into Employee::hours,
   * with that,
   * set new hours : */

  /* set vacation hours : */
  this->vacationHours.hours += this->hours;

  /* save the date of request : */
  this->vacationHours.dateOfRequest = QDate::currentDate();

  /* set salary : */
  this->salaryCalculation();

  /* write the result into QString : */
  result =
      "Vacation hours is now : " + QString::number(this->vacationHours.hours);

  /* return the result : */
  return result;
}

/* this function check if after adding vacation hours, salary become 0 or no */
bool Employee::checkSalaryIncreasingVacHours(QString newHours) {

  int newHoursNumber; // holds the value of newHours in integer

  long long int
      resultOfSalary; // holds the amount of salary after this operation

  /* turn the newHours to integer : */
  newHoursNumber = newHours.toInt();

  /* save the hours into employee::hours for further opeartions : */
  this->hours = newHoursNumber;

  /* if hours was more than 15 before , then we just check the new hours : */
  if (this->vacationHours.hours >= 15) {

    /* finding the final amount of salary : */
    resultOfSalary = this->finalSalary - (newHoursNumber * 100000);

    /* check if salary is positive number return true,
     * if negetive or zero return false : */
    if (resultOfSalary >= 0) {
      return true;
    }
    return false;
  }

  /* if hours will be more than 15 if operation compeletes : */
  else if ((newHoursNumber + this->vacationHours.hours) > 15) {

    /* if salary become more than 15 after this opearation,
     * and was not more than 15 before,
     * then we have to calculate how many hours more than 15?
     * for each of these hours 100000$ will be reduced frome salary : */
    resultOfSalary =
        this->finalSalary -
        (((newHoursNumber + this->vacationHours.hours) - 15) * 100000);

    /* is salary  become negetive then return false,
     * otherwise return true : */
    if (resultOfSalary < 0) {
      return false;
    }
    return true;
  }

  /* and if the hours wont become more than 15 just return true : */
  return true;
}

/* maximum hour for over time work is 12,if full return true */
bool Employee::checkOverTimeWorkIsFull() {

  QDate today; // holds today s' date

  /* consider that we are checking the over time work for this month,
   * so in order to do that,
   * first we check that
   * the last request of over time work was in this month or no,
   * if yes check if full?
   * if no make sure that over time hours for this month is 0:*/

  /* set today s' date : */
  today = QDate::currentDate();

  /* check for last request date : */
  if (today.year() == this->overTimeHours.dateOfRequest.year()) {
    if (today.month() == this->overTimeHours.dateOfRequest.month()) {
      /* now that the last request was in this month ,
       * check if hours are full or no:*/
      if (this->overTimeHours.hours == 12) {

        /* its full , return true : */
        return true;
      }

      /* its not full , return false : */
      return false;
    }
  }

  /* now that there hasnt been any requests for this month,
   * calculate the final salary again,
   * also set the hours 0 which will be done in the function : */
  this->salaryCalculation();

  /* and return false that hours are not full : */
  return false;
}

/* this function return all info of over time hours in this month as QString */
QString Employee::OverTimeHourData() {

  QString data; // hold over time hours data

  /* find how many hours has gotten , and how many hours is left : */
  data = "OverTime hours for this month : " +
         QString ::number(this->overTimeHours.hours) +
         "\nYou can request for " +
         QString::number(12 - this->overTimeHours.hours) + " more hours";

  /* return the data : */
  return data;
}

/* this function gets an integer as parameter
 * that indicate the number of hours requested by user,
 * check if operation is possible or no */
bool Employee::checkOverTimeHoursRequested(QString hoursRequestedInQString) {

  int hoursRequested; // hold hours requested in integer

  /* turn hoursRequestedInQString to integer and set it into hoursRequested : */
  hoursRequested = hoursRequestedInQString.toInt();

  /* save the hours into Employee::hours : */
  this->hours = hoursRequested;

  /* total of requested hours and previous hours should not be more than 12 : */
  if ((this->overTimeHours.hours + hoursRequested) > 12) {
    return false;
  }

  /* if there was no problem with hours requested, return true : */
  return true;
}

/* this function will return
 * the details of increasing over time work as QString : */
QString Employee::increaseOverTimeWorkHour() {

  QString details; // holds the details of increasing overTime work

  details = "After this operation with getting " +
            QString::number(this->hours) +
            " hours over time work \nSalary will be : " +
            QString::number(this->finalSalary) + " + " +
            QString::number((this->hours) * 120000) + " = " +
            QString::number(this->finalSalary + (this->hours * 120000)) +
            "\nClick on go button to confirm...";

  return details;
}

/* this function accomplish increasing overtime work ,
 * also returns the result of operation as QString */
QString Employee::confirmIncreaseOverTimeWorkHour() {

  QString result; // holds the result of operation

  /* set the overtime work : */
  this->overTimeHours.hours += this->hours;

  /* set date of request : */
  this->overTimeHours.dateOfRequest = QDate::currentDate();

  /* set the new salary : */
  this->salaryCalculation();

  /* set the result report : */
  result = "Overtime work : " + QString::number(this->overTimeHours.hours) +
           "\nSalary : " + QString::number(this->finalSalary);

  /* return the result to print on screen : */
  return result;
}

/* this function return personal info of employee as QString */
QString Employee::showPersonalInfo() {

  QString info; // holds pesonal info of employee

  /* first make sure that salary and hours are right : */
  this->salaryCalculation();

  /* set the info into QString::info : */
  info =
      "Name : " + this->getName() + "\nLast name : " + this->getLastName() +
      "\nBirth date : " + QString::number(this->getbirthDate().year()) + " / " +
      QString::number(this->getbirthDate().month()) + " / " +
      QString::number(this->getbirthDate().day()) +
      "\nUser ID : " + QString::number(this->userID) +
      "\nBasic salary : " + QString::number(this->basicSalaryReceived) +
      "\nVacation hours : " + QString::number(this->vacationHours.hours) +
      "                   Amount : - " +
      QString::number(this->vacationHours.amountOfMoney) +
      "\nOvertime work hours : " + QString::number(this->overTimeHours.hours) +
      "          Amount : + " +
      QString::number(this->overTimeHours.amountOfMoney) +
      "\nFinal salary : " + QString::number(this->finalSalary);

  return info;
}

/* this function gets a number and a vector of clients as parameter,
 * trys to find the client who that number is its national code,
 * if any client founds return true */
bool Employee::findAClient(long int nationalCode, std::vector<Client> clients) {

  /* in this loop we check all clients national codes : */
  for (int i = 0; i < (int)clients.size(); i++) {

    /* national code matches? */
    if (clients[i].getNationalCode() == nationalCode) {

      /* save index of client for further operations : */
      this->indexOfClient = i;

      /* return true as we found the client : */
      return true;
    }
  }

  /* client was not found return fales : */
  return false;
}

/* this function gets vector of clients ,
 * returns info of one of these clients in QString */
QString Employee::showClientInfo(std::vector<Client> clients) {

  /* we had stored the index of client we want in employee::indexOfClient */

  return clients[this->indexOfClient].showClientInfo() +
         "\n\nAcounts in this bank:\n____________________________________\n" +
         clients[this->indexOfClient].showAllAccountsInfo();
}

/* this function creates account for a client */
void Employee::createAccountForClient(std::vector<Client> &clients,
                                      QString initialAmountInString) {

  long long int initalAmount; // holds the inital amount in long long int

  Account theAccount; // the account we wana add

  QDate today; // holds todays date

  QString accountNumber; // holds the number of the account we wana create

  /* set todays date : */
  today = QDate::currentDate();

  /* turn the QString to long long : */
  initalAmount = initialAmountInString.toLongLong();

  /* create account : */

  /* step 1:create number of accuont which is a mix of owner info : */

  /* number = [time created] + [date created] + [national code] : */
  accountNumber =
      QString::number(QTime::currentTime().second()) +
      QString::number(QTime::currentTime().minute()) +
      QString::number(QTime::currentTime().hour()) +
      QString::number(today.day()) + QString::number(today.month()) +
      QString::number(today.year()) +
      QString ::number(clients[this->indexOfClient].getNationalCode());

  /* make sure account number is has 13 digit : */
  if (accountNumber.size() > 13) {
    accountNumber.chop(accountNumber.size() - 13);
  }

  /* set number into account : */
  theAccount.setAccountNumber(accountNumber.toLongLong());

  /* step 2:set national code : */
  theAccount.setNaionalCode(clients[this->indexOfClient].getNationalCode());

  /* step 3:set date opened : */
  theAccount.setOpeningDate(today);

  /* step 4:set initial amount : */
  theAccount.setBalance(initalAmount);

  /* step 5:set it active : */
  theAccount.setActive(true);

  /* step 6:push back this account : */
  clients[this->indexOfClient].addAccount(theAccount);
}

/* this function adds a new client with the info got in parameter
 * creates an account for this new client */
void Employee::createAccountForNewClient(std::vector<Client> &clients,
                                         QString nationalCode, QString name,
                                         QString lastName, QString birthYear,
                                         QString birthMonth, QString birthDay,
                                         QString userName, QString password,
                                         QString initialAmount) {
  Client newClient; // holds our new client

  /* set info of clients : */

  /* step 1: set name : */
  newClient.setName(name);

  /* step 2: set last name : */
  newClient.setLastName(lastName);

  /* step 3: set birth date : */
  newClient.setBirthDate(birthDay.toInt(), birthMonth.toInt(),
                         birthYear.toInt());

  /* step 4: set userName : */
  newClient.setUserName(userName);

  /* step 5: set password : */
  newClient.setPassword(password);

  /* step 6: set national code : */
  newClient.setNationalCode(nationalCode.toLong());

  /* step 7: push back this new client : */
  clients.push_back(newClient);

  /* save the index of this client in vector,
   * this is usefull in further operations : */
  this->indexOfClient = clients.size() - 1;

  /* create new account for this client : */
  this->createAccountForClient(clients, initialAmount);
}

/* this function checks between all clients account numbers,
 * if found the account
 * return true */
bool Employee::searchForAccount(std::vector<Client> &clients,
                                QString accountNumberInString) {

  long long int accountNumber; // holds account number in integer

  int indexOfAccount; // holds the index of account

  /* turn QString into long long integer : */
  accountNumber = accountNumberInString.toLongLong();

  /* search in clients : */
  for (int i = 0; i < (int)clients.size(); i++) {

    /* find account : */
    indexOfAccount = clients[i].findTheAccountOfTheClient(accountNumber);

    if (indexOfAccount != -1) {

      /* account found,
       * save client index,
       * return true : */
      this->indexOfClient = i;
      return true;
    }
  }

  /* could not find the account,
   * return false : */
  return false;
}

/* this function gets the clients and acccount number as parameter,
 * delete the account,
 * if delete client return 1,
 * if delete only account return 2 */
int Employee::deleteAccount(std::vector<Client> &clients,
                            QString accountNumber) {

  /* 1.this is the last account of this client : */
  if (clients[this->indexOfClient].getSizeOfAccount() == 1) {

    /* then we also have to delete the client : */
    clients.erase(clients.begin() + this->indexOfClient);
    return 1;
  }

  /* 2.this is not the only account of this client : */
  else {

    clients[this->indexOfClient].deleteAccount(accountNumber.toLongLong());
    return 2;
  }
}
