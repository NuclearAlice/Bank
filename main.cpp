/******************************************************
** File            :   main.cpp
** Date            :   2022/7/20
** This File contains main function
******************************************************/
#include "aliceBank.h"

#include <QApplication>

#include "bank.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  AliceBank w;
  w.show();
  return a.exec();
}
