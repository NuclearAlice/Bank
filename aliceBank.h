#ifndef ALICEBANK_H
#define ALICEBANK_H

#include "bank.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class AliceBank;
}
QT_END_NAMESPACE

class AliceBank : public QMainWindow {
  Q_OBJECT

public:
  AliceBank();
  ~AliceBank();

private slots:

  /*get info from file and set it:*/
  bool setManagerData();

  bool setEmployeeData();

  bool setClientData();

  /*show errors or warnings:*/

  void errorOccured(int);

  /*check if line edit is valid:*/
  bool checkIfLineEditValidNewClient();

  /*hidings:*/

  void hideAllWidgets();

  void hideMenuButtonsForClients();

  void hideNonMenuButtonsForClients();

  void hideNonMenuButtonsForEmployee();

  void hideMenuButtonsForEmployee();

  void hideInfoButtonsClientWidget();

  /*show butthons:*/

  void showNonMenuButtonsForClients();

  void showMenuButtonsForClients();

  void showMenuButtonsForEmployee();

  void showNonMenuButtonsForEmployee();

  void showInfoButtonsClientWidget();

  /*clear line edits for new widget:*/
  void clearLineEditsNewClientWidget();
  void clearLineEditsHireEmployeeWidget();

  /*show logins:*/

  void showClientLogin();

  void showEmployeeLogin();

  /*set the name of user into lable on profile widget:*/

  void setNameClient();
  void setNameEmployee();

  /*record the operation into report.txt:*/

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

  void record(int);

  /*clicking on pushbuttons:*/

  void on_pushButton_alice_start_clicked();

  void on_pushButton_Client_clicked();

  void on_pushButton_Employee_clicked();

  void on_pushButton_close_program_clicked();

  void on_pushButton_client_back_clicked();

  void on_pushButton_employee_back_clicked();

  void on_pushButton_client_enter_clicked();

  void on_pushButton_employee_enter_clicked();

  void on_pushButton_client_close_clicked();

  void on_pushButton_client_increase_account_balance_clicked();

  void on_pushButton_client_back_to_client_menu_clicked();

  void on_pushButton_client_select_account_clicked();

  void on_pushButton_client_enter_amount_clicked();

  void on_pushButton_client_withdraw_clicked();

  void on_pushButton_client_show_info_clicked();

  void on_pushButton_client_show_account_info_clicked();

  void on_pushButton_employee_close_clicked();

  void on_pushButton_employee_leave_request_clicked();

  void on_pushButton_employee_back_to_employee_menu_clicked();

  void on_pushButton_employee_enter_text_clicked();

  void on_pushButton_employee_go_clicked();

  void on_pushButton_employee_overtime_request_clicked();

  void on_pushButton_employee_show_pesonal_info_clicked();

  void on_pushButton_employee_show_client_info_clicked();

  void on_pushButton_employee_create_account_for_a_client_clicked();

  void on_pushButton_employee_create_account_already_client_clicked();

  void on_pushButton_employee_create_account_new_client_clicked();

  void on_pushButton_employee_new_account_new_client_back_clicked();

  void on_pushButton_employee_new_account_new_client_go_clicked();

  void on_pushButton_employee_delete_account_of_a_client_clicked();

  void on_pushButton_employee_show_employee_info_clicked();

  void on_pushButton_employee_hire_employee_clicked();

  void on_pushButton_manager_hire_employee_go_clicked();

  void on_pushButton_manager_hire_employee_back_clicked();

  void on_pushButton_employee_fire_employee_clicked();

private:
  Ui::AliceBank *ui;
  QMessageBox qMessageBox;
  Bank myBank;
};
#endif // ALICEBANK_H
