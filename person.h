/******************************************************
** File            :   person.h
** Date            :   2022/7/20
** This File contains class Person
******************************************************/

#ifndef PERSON_H
#define PERSON_H

#include <QDateTime>
#include <QString>

class Person {
public:
  /*constructor function*/
  Person();

  /*setter functions*/
  void setName(QString name) { this->name = name; }
  void setLastName(QString lastName) { this->lastName = lastName; }
  void setBirthDate(int day, int month, int year) {
    this->birthDate.setDate(year, month, day);
  }
  void setUserName(QString userName) { this->userName = userName; }
  void setPassword(QString password) { this->password = password; }

  /*getter functions:*/
  QString getName() { return name; }
  QString getLastName() { return lastName; }
  QDate getbirthDate() { return birthDate; }
  QString getUserName() { return userName; }
  QString getPassword() { return password; }

private:
  QString name;
  QString lastName;
  QDate birthDate;
  QString userName;
  QString password;
};

#endif // PERSON_H
