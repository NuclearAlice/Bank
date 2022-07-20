#include "aliceBank.h"
#include "ui_aliceBank.h"
#include <QDateTime>
#include <QPixmap>

AliceBank::AliceBank() : QMainWindow(), ui(new Ui::AliceBank) {
  ui->setupUi(this);
  this->hideAllWidgets();
  ui->widget_alice_start->show();
  QPixmap pix("/home/alice/Pictures/AliceBank.jpg");
  ui->label_bank_image->setPixmap(pix.scaled(500, 600, Qt::KeepAspectRatio));
  ui->label_bank_start_image->setPixmap(
      pix.scaled(500, 600, Qt::KeepAspectRatio));
}

AliceBank::~AliceBank() { delete ui; }

bool AliceBank::setManagerData() {
  if (!(this->myBank.setManagerDataFromFile())) {
    this->errorOccured(2);
    return false;
  }
  return true;
}

bool AliceBank::setEmployeeData() {
  if (!(this->myBank.setEmployeeDataFromFile())) {
    this->errorOccured(4);
    return false;
  }
  return true;
}
bool AliceBank::setClientData() {
  if (!(this->myBank.setClientsDataFromFile())) {
    this->errorOccured(5);
    return false;
  }
  return true;
}

void AliceBank::errorOccured(int ex) {

  switch (ex) {
  case 1:
    QMessageBox::warning(this, "Warning 1",
                         "User name and password must be filled!");
    break;
  case 2:
    QMessageBox::warning(this, "Warning 2",
                         "Could not find bank data!\nSorry:(");
    break;

  case 3:
    QMessageBox::warning(this, "Warning 3", "User name/password is not valid!");
    break;

  case 4:
    QMessageBox::warning(this, "Warning 4",
                         "Could not find employees data!\nSorry:(");
    break;
  case 5:
    QMessageBox::warning(this, "Warning 5",
                         "Could not find clients data!\nSorry:(");
    break;
  case 6:
    QMessageBox::warning(this, "Warning 6",
                         "Somthing is wrong with report.txt file!");
    break;

  case 7:
    QMessageBox::warning(this, "Warning 7", "Enter a number!");
    break;

  case 8:
    QMessageBox::warning(this, "Warning 8", "Account number is invalid!");
    break;

  case 9:
    QMessageBox::warning(this, "Warning 9", "Line edit must be filled!");
    break;

  case 10:
    QMessageBox::warning(this, "Warning 10", "Amount can not be zero!");
    break;

  case 11:
    QMessageBox::warning(this, "Warning 11", "Not enough balance for withraw!");
    break;

  case 12:
    QMessageBox::warning(this, "Warning 12", "This number is too big!");
    break;

  case 13:
    QMessageBox::warning(this, "Warning 13",
                         "Salary becomes negative\nSo it is not possible!");
    break;

  case 14:
    QMessageBox::warning(this, "Warning 14",
                         "OverTime work for this month is full!");
    break;

  case 15:
    QMessageBox::warning(this, "Warning 15",
                         "Can not request more than 12 hours in each month!");
    break;

  case 16:
    QMessageBox::warning(this, "Warning 16", "National code is invalid!");
    break;

  case 17:
    QMessageBox::warning(this, "Warning 17",
                         "Inital amount can not be less than 50000!");
    break;

  case 18:
    QMessageBox::warning(this, "Warning 18",
                         "there is already a client with such national code!");
    break;

  case 19:
    QMessageBox::warning(this, "Warning 19", "Birth date is invalid!");
    break;

  case 20:
    QMessageBox::warning(this, "Warning 20",
                         "Enter number for birth date/inital amount!");
    break;

  case 21:
    QMessageBox::warning(this, "Warning 21", "National code has 10 digits!");
    break;

  case 22:
    QMessageBox::warning(this, "Warning 22", "User id is invalid!");
    break;

  case 23:
    QMessageBox::warning(this, "Warning 23",
                         "Enter number for user id/birth date/salary!");
    break;

  case 24:
    QMessageBox::warning(this, "Warning 24", "User id has 3 digits!");
    break;

  case 25:
    QMessageBox::warning(
        this, "Warning 25",
        "This is you manager Alice!\nYou can not fire yourself!!");
    break;

  default:
    QMessageBox::warning(this, "Warning", "Some kind of error occured!");
    break;
  }
}

/*this function checks if all info in line edits are valid or not, this is for
 * employee_new_client:*/
bool AliceBank::checkIfLineEditValidNewClient() {

  /*first check if all line edits are full:*/
  if ((this->ui->lineEdit_employee_new_account_new_client_name->text() == "") ||
      (this->ui->lineEdit_employee_new_account_new_client_last_name->text() ==
       "") ||
      (this->ui->lineEdit_employee_new_account_new_client_birth_year->text() ==
       "") ||
      (this->ui->lineEdit_employee_new_account_new_client_birth_month->text() ==
       "") ||
      (this->ui->lineEdit_employee_new_account_new_client_birth_day->text() ==
       "") ||
      (this->ui->lineEdit_employee_new_account_new_client_user_name->text() ==
       "") ||
      (this->ui->lineEdit_employee_new_account_new_client_password->text() ==
       "") ||
      (this->ui->lineEdit_employee_new_account_new_client_initial_amount
           ->text() == "")) {
    errorOccured(9);
    return false;
  }

  /*now that line edits are full check if number line edits are filled with
   * number or no:*/
  else if (!(

               myBank.checkNumber(
                   ui->lineEdit_employee_new_account_new_client_birth_year
                       ->text()) &&
               myBank.checkNumber(
                   ui->lineEdit_employee_new_account_new_client_birth_month
                       ->text()) &&
               myBank.checkNumber(
                   ui->lineEdit_employee_new_account_new_client_birth_day
                       ->text()) &&
               myBank.checkNumber(
                   ui->lineEdit_employee_new_account_new_client_initial_amount
                       ->text()))) {
    errorOccured(20);
    return false;
  }

  /*check if birth date is valid or not:*/
  else if (!(QDate::isValid(
               ui->lineEdit_employee_new_account_new_client_birth_year->text()
                   .toInt(),
               ui->lineEdit_employee_new_account_new_client_birth_month->text()
                   .toInt(),
               ui->lineEdit_employee_new_account_new_client_birth_day->text()
                   .toInt()))) {

    errorOccured(19);
    return false;
  }

  /*check if user name and password is valid or no, there should not be any
   * client or employee with this user name and password:*/
  else if (this->myBank.searchForPasswordAndUserName(
               this->ui->lineEdit_employee_new_account_new_client_user_name
                   ->text(),
               this->ui->lineEdit_employee_new_account_new_client_password
                   ->text())) {
    errorOccured(3);
    return false;
  }

  /*check if initial amount is less than 50000:*/
  else if (this->ui->lineEdit_employee_new_account_new_client_initial_amount
               ->text()
               .toLongLong() < 50000) {

    errorOccured(17);
    return false;
  }

  /*no problem with inputs,return true:*/
  return true;
}

void AliceBank::hideAllWidgets() {
  ui->widget_alice->hide();
  ui->widget_alice_start->hide();
  ui->widget_client->hide();
  ui->widget_employee->hide();
  ui->widget_client_entered_show_menu->hide();
  ui->widget_employee_entered_show_menu->hide();
  ui->widget_employee_new_client->hide();
  ui->widget_manager_hire_employee->hide();
}

void AliceBank::hideMenuButtonsForClients() {
  ui->pushButton_client_increase_account_balance->hide();
  ui->pushButton_client_withdraw->hide();
  ui->pushButton_client_show_info->hide();
}

void AliceBank::hideNonMenuButtonsForClients() {
  ui->textBrowser_client_info_and_account_numbers->hide();
  ui->pushButton_client_back_to_client_menu->hide();
  ui->lineEdit_client_select_account->hide();
  ui->pushButton_client_select_account->hide();
  ui->pushButton_client_enter_amount->hide();
  ui->pushButton_client_show_account_info->hide();
}

void AliceBank::hideNonMenuButtonsForEmployee() {
  ui->textBrowser_employee_show_info->hide();
  ui->pushButton_employee_back_to_employee_menu->hide();
  ui->lineEdit_Employee_enter_text->hide();
  ui->pushButton_employee_enter_text->hide();
  ui->pushButton_employee_go->hide();
  ui->pushButton_employee_show_account_info_of_a_client->hide();
  ui->pushButton_employee_create_account_already_client->hide();
  ui->pushButton_employee_create_account_new_client->hide();
}

void AliceBank::hideMenuButtonsForEmployee() {
  ui->pushButton_employee_leave_request->hide();
  ui->pushButton_employee_overtime_request->hide();
  ui->pushButton_employee_show_pesonal_info->hide();
  ui->pushButton_employee_show_client_info->hide();
  ui->pushButton_employee_create_account_for_a_client->hide();
  ui->pushButton_employee_delete_account_of_a_client->hide();
  ui->pushButton_employee_show_employee_info->hide();
  ui->pushButton_employee_hire_employee->hide();
  ui->pushButton_employee_fire_employee->hide();
}

void AliceBank::hideInfoButtonsClientWidget() {

  ui->lineEdit_employee_new_account_new_client_name->hide();
  ui->lineEdit_employee_new_account_new_client_last_name->hide();
  ui->lineEdit_employee_new_account_new_client_birth_year->hide();
  ui->lineEdit_employee_new_account_new_client_birth_month->hide();
  ui->lineEdit_employee_new_account_new_client_birth_day->hide();
  ui->lineEdit_employee_new_account_new_client_user_name->hide();
  ui->lineEdit_employee_new_account_new_client_password->hide();
  ui->lineEdit_employee_new_account_new_client_initial_amount->hide();

  ui->label_employee_new_account_new_client_name->hide();
  ui->label_employee_new_account_new_client_last_name->hide();
  ui->label_employee_new_account_new_client_birth_date->hide();
  ui->label_employee_new_account_new_client_user_name->hide();
  ui->label_employee_new_account_new_client_password->hide();
  ui->label_employee_new_account_new_client_initial_amount->hide();
}

void AliceBank::showNonMenuButtonsForClients() {
  this->ui->pushButton_client_select_account->show();
  this->ui->pushButton_client_back_to_client_menu->show();
  this->ui->lineEdit_client_select_account->show();
  this->ui->textBrowser_client_info_and_account_numbers->show();
}

void AliceBank::showNonMenuButtonsForEmployee() {
  this->ui->pushButton_employee_enter_text->show();
  this->ui->pushButton_employee_back_to_employee_menu->show();
  this->ui->lineEdit_Employee_enter_text->show();
  this->ui->textBrowser_employee_show_info->show();
}

void AliceBank::showMenuButtonsForClients() {
  ui->pushButton_client_increase_account_balance->show();
  ui->pushButton_client_withdraw->show();
  ui->pushButton_client_show_info->show();
}

void AliceBank::showMenuButtonsForEmployee() {

  ui->pushButton_employee_leave_request->show();
  ui->pushButton_employee_overtime_request->show();
  ui->pushButton_employee_show_pesonal_info->show();
  ui->pushButton_employee_show_client_info->show();
  ui->pushButton_employee_create_account_for_a_client->show();
  ui->pushButton_employee_delete_account_of_a_client->show();

  /*check if employee is manager,show manager buttons:*/
  if (this->myBank.getIndex() == 0) {
    ui->pushButton_employee_show_employee_info->show();
    ui->pushButton_employee_hire_employee->show();
    ui->pushButton_employee_fire_employee->show();
  }
}

/*this function shows info buttons of new client widget:*/
void AliceBank::showInfoButtonsClientWidget() {
  ui->lineEdit_employee_new_account_new_client_name->show();
  ui->lineEdit_employee_new_account_new_client_last_name->show();
  ui->lineEdit_employee_new_account_new_client_birth_year->show();
  ui->lineEdit_employee_new_account_new_client_birth_month->show();
  ui->lineEdit_employee_new_account_new_client_birth_day->show();
  ui->lineEdit_employee_new_account_new_client_user_name->show();
  ui->lineEdit_employee_new_account_new_client_password->show();
  ui->lineEdit_employee_new_account_new_client_initial_amount->show();

  ui->label_employee_new_account_new_client_name->show();
  ui->label_employee_new_account_new_client_last_name->show();
  ui->label_employee_new_account_new_client_birth_date->show();
  ui->label_employee_new_account_new_client_user_name->show();
  ui->label_employee_new_account_new_client_password->show();
  ui->label_employee_new_account_new_client_initial_amount->show();
}

/*this function clears all line edits in new client widget:*/
void AliceBank::clearLineEditsNewClientWidget() {

  ui->lineEdit_employee_new_account_new_client_national_code->clear();
  ui->lineEdit_employee_new_account_new_client_name->clear();
  ui->lineEdit_employee_new_account_new_client_last_name->clear();
  ui->lineEdit_employee_new_account_new_client_birth_year->setText("Year");
  ui->lineEdit_employee_new_account_new_client_birth_month->setText("month");
  ui->lineEdit_employee_new_account_new_client_birth_day->setText("day");
  ui->lineEdit_employee_new_account_new_client_user_name->clear();
  ui->lineEdit_employee_new_account_new_client_password->clear();
  ui->lineEdit_employee_new_account_new_client_initial_amount->clear();
}

/*this function clears all line edits in hire employee widget:*/
void AliceBank::clearLineEditsHireEmployeeWidget() {

  ui->lineEdit_manager_hire_employee_userid->clear();
  ui->lineEdit_manager_hire_employee_name->clear();
  ui->lineEdit_manager_hire_employee_last_name->clear();
  ui->lineEdit_manager_hire_employee_birth_year->setText("Year");
  ui->lineEdit_manager_hire_employee_birth_month->setText("month");
  ui->lineEdit_manager_hire_employee_birth_day->setText("day");
  ui->lineEdit_manager_hire_employee_user_name->clear();
  ui->lineEdit_manager_hire_employee_password->clear();
  ui->lineEdit_manager_hire_employee_salary->clear();
}

/*this function will look for client name that has login , set the name on lable
 * so we can show it in profile widget*/
void AliceBank::setNameClient() {

  /*the client index is saved in Bank::index, get the index and pass it to
   * Bank::getClient as parameter and this function returns that client, call
   * for Person::getName so get the name and set the name into client name
   * lable:*/
  this->ui->label_client_name_show->setText(this->myBank.getClient().getName());
}

/*this function will look for employee name that has login , set the name on
 * lable so we can show it in profile widget*/
void AliceBank::setNameEmployee() {

  /*the employee index is saved in Bank::index, get the index and pass it to
   * Bank::getEmployee as parameter and this function returns that employee,
   * call for Person::getName so get the name and set the name into employee
   * name lable:*/
  this->ui->label_employee_name_show->setText(
      this->myBank.getEmployee().getName());
}

/*function that set the default setting for client*/
void AliceBank::showClientLogin() {

  /*first of all record that client has login into report.txt file with exact
   * time and date:*/
  this->record(1);

  /*hide all widgets:*/
  this->hideAllWidgets();

  /*now in the client widget profile ,
   *hide all parts that dont belong to client menu:*/
  this->hideNonMenuButtonsForClients();

  /*show client menu buttons:*/
  this->showMenuButtonsForClients();

  /*set the name of client to name lable ,
   *so that it can be shown on client profile*/
  this->setNameClient();

  /*print welcome message to client:*/
  QMessageBox::about(this, "Welcome", "welcom to alice bank!");

  /*show client widget:*/
  this->ui->widget_client_entered_show_menu->show();
}

/*function that set the default setting for manager*/
void AliceBank::showEmployeeLogin() {

  /*first of all record that employee has login into report.txt file with exact
   * time and date:*/
  this->record(5);

  /*hide all widgets:*/
  this->hideAllWidgets();

  /*now in the employee widget profile ,hide all parts:*/
  this->hideNonMenuButtonsForEmployee();
  this->hideMenuButtonsForEmployee();

  /*show Employee menu buttons:*/
  this->showMenuButtonsForEmployee();

  /*set the name of employee to name lable ,
   *so that it can be shown on manager profile*/
  this->setNameEmployee();

  /*print welcome message to employee:*/
  QMessageBox::about(this, "Welcome", "welcom to alice bank!");

  /*show client widget:*/
  this->ui->widget_employee_entered_show_menu->show();
}

void AliceBank::record(int typeOfRecord) {
  if (!myBank.record(typeOfRecord)) {
    errorOccured(6);
  }
}
void AliceBank::on_pushButton_Client_clicked() {
  this->hideAllWidgets();
  ui->widget_client->show();
}

void AliceBank::on_pushButton_Employee_clicked() {
  this->hideAllWidgets();
  ui->widget_employee->show();
}

void AliceBank::on_pushButton_close_program_clicked() {

  /*save all info to files:*/
  myBank.save();

  /*close program:*/
  this->close();
}

void AliceBank::on_pushButton_client_back_clicked() {
  this->hideAllWidgets();
  ui->widget_alice->show();
}

void AliceBank::on_pushButton_employee_back_clicked() {
  this->hideAllWidgets();
  ui->widget_alice->show();
}

void AliceBank::on_pushButton_client_enter_clicked() {
  myBank.setUserName(ui->lineEdit_client_user_name->text());
  myBank.setPassword(ui->lineEdit_client_password->text());
  if (myBank.getUserName() == "" || myBank.getPassword() == "") {
    errorOccured(1);
  } else {
    if (!myBank.searchForClientUserNamesAndPasswords()) {
      errorOccured(3);
    } else {

      this->ui->lineEdit_client_user_name->clear();
      this->ui->lineEdit_client_password->clear();

      this->showClientLogin();
    }
  }
}

void AliceBank::on_pushButton_employee_enter_clicked() {

  /*save the userName and password entered in line edit into Bank::username and
   * Bank::password,this is for further operations such as checking if it is
   * valid or matches to any of employees*/
  myBank.setUserName(ui->lineEdit_employee_user_name->text());
  myBank.setPassword(ui->lineEdit_employee_password->text());

  /*check if the fields are empty or no,if yes,give a warning:*/
  if (myBank.getUserName() == "" || myBank.getPassword() == "") {
    errorOccured(1);
  }

  /*check employee userNames and passwords:*/
  else if (!(myBank.searchForEmployeeUserNamesAndPasswords())) {

    /*if no employee found then just give a warning that userName or password is
     * not valid:*/
    errorOccured(3);

  }

  /*userName and password are valid,login:*/
  else {

    /*employee found,clear lineEdits:*/
    this->ui->lineEdit_employee_user_name->clear();
    this->ui->lineEdit_employee_password->clear();

    /*login employee profile:*/
    this->showEmployeeLogin();
  }
}

void AliceBank::on_pushButton_alice_start_clicked() {

  /*set all info of bank from files,if setting operation was successful,go to
   * main menu,if not,give a warning:*/
  if (setManagerData() == true && setEmployeeData() == true &&
      setClientData() == true) {

    /*now hide start widget and go for main manu widget:*/
    ui->widget_alice_start->hide();
    ui->widget_alice->show();
  }

  /*setting failed,give a warning:*/
  else {
    this->close();
  }
}

void AliceBank::on_pushButton_client_close_clicked() {
  this->hideMenuButtonsForClients();
  this->hideNonMenuButtonsForClients();
  this->hideAllWidgets();
  this->ui->widget_alice->show();
  this->ui->textBrowser_client_info_and_account_numbers->clear();
  this->ui->lineEdit_client_select_account->clear();
}

void AliceBank::on_pushButton_client_increase_account_balance_clicked() {
  myBank.getClientByReference().setOperationNumberInMenu(1);
  this->hideMenuButtonsForClients();
  this->showNonMenuButtonsForClients();
  this->ui->lineEdit_client_select_account->setText(
      "Enter account number here");
  this->ui->textBrowser_client_info_and_account_numbers->setText(
      myBank.getClient().showNumbersOfAccounts());
}

void AliceBank::on_pushButton_client_back_to_client_menu_clicked() {
  hideNonMenuButtonsForClients();
  this->showMenuButtonsForClients();
  this->ui->textBrowser_client_info_and_account_numbers->clear();
  this->ui->lineEdit_client_select_account->clear();
}

void AliceBank::on_pushButton_client_select_account_clicked() {

  /*check if the text is a number or not, if its not, give a warning*/
  if (!(myBank.checkNumber(ui->lineEdit_client_select_account->text()))) {
    errorOccured(7);
  }

  /*if the text is a number,
   *then check if this number is realy an account number,if not,give a
   *warning*/
  else if (!myBank.checkForValidAccountNumber(
               ui->lineEdit_client_select_account->text())) {
    errorOccured(8);
  }

  /*if valid print it on screen*/
  else {
    this->ui->textBrowser_client_info_and_account_numbers->setText(
        this->myBank.getAccountInfo());
    this->ui->lineEdit_client_select_account->setText("Enter amount");
    this->ui->pushButton_client_select_account->hide();
    this->ui->pushButton_client_enter_amount->show();
  }
}

void AliceBank::on_pushButton_client_enter_amount_clicked() {

  /*check if line edit is empty or not*/
  if (this->ui->lineEdit_client_select_account->text() == "") {
    errorOccured(9);
  }

  /*check if the text is a number or not, if its not, give a warning*/
  else if (!(myBank.checkNumber(ui->lineEdit_client_select_account->text()))) {
    errorOccured(7);
  }

  /*check of the number has more digits than long long int*/
  else if (this->ui->lineEdit_client_select_account->text().size() > 18) {
    errorOccured(12);
  }

  /*check if number is 0,if yes,give a warning*/
  else if (ui->lineEdit_client_select_account->text() == "0") {
    errorOccured(10);
  }

  /*if a number do the operation for balance*/
  else {

    /*add balance :*/
    if (myBank.getClient().getOperationNumberInMenu() == 1) {

      /*give the number from line edit to the function client::add balance to do
       * the adding operation: */
      myBank.getClientByReference().addBalanceToAccount(
          ui->lineEdit_client_select_account->text());

      /*save the amount that has been added to balance into bank::reportInfo,for
       * wirting in file report.txt*/
      myBank.setReportInfo(ui->lineEdit_client_select_account->text());

      /*call the record function to record the adding operation in file
       * report.txt:*/
      this->record(2);

      /*set the line edit to print done messege:*/
      this->ui->lineEdit_client_select_account->setText("Done");
    }

    /*withdraw :*/
    else if (myBank.getClient().getOperationNumberInMenu() == 2) {
      /*check if there is enough balance to withraw,here the function
       * client::withdraw will return boolean ,if true means withdraw was
       * possible and has been done,if false,then there is no enough balance and
       * warning will come to screen*/

      if (myBank.getClientByReference().withdraw(
              ui->lineEdit_client_select_account->text())) {
        /*now that the withdraw operation was successful,give the amount to
         * bank::reportinfo so that can be use to write and record the operation
         * into report.txt file*/
        myBank.setReportInfo("-" + ui->lineEdit_client_select_account->text());

        /*call the record function to record the withdraw operation in file
         * report.txt:*/
        this->record(3);

        /*set the line edit to print done messege:*/
        this->ui->lineEdit_client_select_account->setText("Done");
      }

      /*if there was not enough balance to withraw ,then the operation
       * failed,the warning will come to screen*/
      else {
        errorOccured(11);
      }
    }

    /*set info again and print it on screen:*/
    this->ui->textBrowser_client_info_and_account_numbers->setText(
        this->myBank.getAccountInfo());
  }
}

void AliceBank::on_pushButton_client_withdraw_clicked() {
  myBank.getClientByReference().setOperationNumberInMenu(2);
  this->hideMenuButtonsForClients();
  this->showNonMenuButtonsForClients();
  this->ui->lineEdit_client_select_account->setText(
      "Enter account number here");
  this->ui->textBrowser_client_info_and_account_numbers->setText(
      myBank.getClient().showNumbersOfAccounts());
}

void AliceBank::on_pushButton_client_show_info_clicked() {
  this->hideMenuButtonsForClients();
  this->ui->textBrowser_client_info_and_account_numbers->show();
  this->ui->pushButton_client_back_to_client_menu->show();
  this->ui->pushButton_client_show_account_info->show();
  ui->textBrowser_client_info_and_account_numbers->setText(
      this->myBank.getClient().showClientInfo());
}

void AliceBank::on_pushButton_client_show_account_info_clicked() {
  this->ui->pushButton_client_show_account_info->hide();
  this->ui->textBrowser_client_info_and_account_numbers->setText(
      myBank.getClient().showAllAccountsInfo());
}

void AliceBank::on_pushButton_employee_close_clicked() {
  this->hideMenuButtonsForEmployee();
  this->hideNonMenuButtonsForEmployee();
  this->hideAllWidgets();
  this->ui->widget_alice->show();
  this->ui->textBrowser_employee_show_info->clear();
  this->ui->lineEdit_Employee_enter_text->clear();
}

void AliceBank::on_pushButton_employee_leave_request_clicked() {

  /*hide menu buttons to get to next stage:*/
  this->hideMenuButtonsForEmployee();

  /*show non menu buttons:*/
  this->showNonMenuButtonsForEmployee();

  /*show vacation hours for this month:*/
  this->ui->textBrowser_employee_show_info->setText(
      this->myBank.getEmployeeByReference().showVacationHours());

  /*set messege enter hours into line edit:*/
  this->ui->lineEdit_Employee_enter_text->setText("Enter hour");

  /*save the number of operation menu into employee::operationNumberInMenu::*/
  this->myBank.getEmployeeByReference().setOperationNumberInMenu(1);
}

void AliceBank::on_pushButton_employee_back_to_employee_menu_clicked() {
  this->hideNonMenuButtonsForEmployee();
  this->showMenuButtonsForEmployee();
  this->ui->textBrowser_employee_show_info->clear();
  this->ui->lineEdit_Employee_enter_text->clear();
}

void AliceBank::on_pushButton_employee_enter_text_clicked() {

  /*check if the line edit is empty or not, of yes give a warning:*/
  if (this->ui->lineEdit_Employee_enter_text->text() == "") {
    errorOccured(9);
  }

  /*check if the entered QString in line edit is a number or no*/
  else if (!(this->myBank.checkNumber(
               this->ui->lineEdit_Employee_enter_text->text()))) {
    errorOccured(7);
  }

  /*check if the number is 0 or not*/
  else if (this->ui->lineEdit_Employee_enter_text->text() == "0") {

  }

  /*see in which operation this button is pressed:*/
  else {

    /*if employee::operationNumberInMenu was 1, then we are about to request for
     * vacation hour:*/
    if (this->myBank.getEmployee().getOperationNumberInMenu() == 1) {

      /*check if the salary wont be negative after increasing operation:*/
      if (myBank.getEmployeeByReference().checkSalaryIncreasingVacHours(
              this->ui->lineEdit_Employee_enter_text->text())) {

        /*call for increasing vacation hours function, this fucntion return a
         * QString as the info of adding operation,set the QString into
         * textBrowser:*/
        this->ui->textBrowser_employee_show_info->setText(
            this->myBank.getEmployeeByReference().increaseVacationHour());

        /*set the buttons:*/

        /*now hide the lineEdit:*/
        this->ui->lineEdit_Employee_enter_text->hide();
        /*hide the enter text push button:*/
        this->ui->pushButton_employee_enter_text->hide();
        /*show the go button:*/
        this->ui->pushButton_employee_go->show();

      }

      /*if salary become negetive,give a warning:*/
      else {
        errorOccured(13);
      }
    }

    /*if employee::operationNumberInMenu was 2, then we are about to request for
     * overTime hours:*/
    else if (this->myBank.getEmployee().getOperationNumberInMenu() == 2) {

      /*check if hours in line text is possible:*/
      if (this->myBank.getEmployeeByReference().checkOverTimeHoursRequested(
              this->ui->lineEdit_Employee_enter_text->text())) {

        /*set the details of opetaion in textBrowser to show on screen:*/
        this->ui->textBrowser_employee_show_info->setText(
            this->myBank.getEmployee().increaseOverTimeWorkHour());

        /*set the buttons:*/

        /*now hide the lineEdit:*/
        this->ui->lineEdit_Employee_enter_text->hide();
        /*hide the enter text push button:*/
        this->ui->pushButton_employee_enter_text->hide();
        /*show the go button:*/
        this->ui->pushButton_employee_go->show();

      }

      /*now that new hours will be more than 12,give a warning:*/
      else {
        errorOccured(15);
      }
    }

    /*if employee::operationNumberInMenu was 3, then we want to show a client s'
     * info on screen:*/
    else if (this->myBank.getEmployee().getOperationNumberInMenu() == 3) {

      /*check if national code is valid or not, find the client and save its
       * index into Employee::indexOfClient:*/
      if (myBank.findClientByNationalCode(
              this->ui->lineEdit_Employee_enter_text->text())) {

        /*client is found set its info on screen:*/
        this->ui->textBrowser_employee_show_info->setText(
            this->myBank.getEmployee().showClientInfo(
                this->myBank.getVectorOfClients()));

      }

      /*national code was not valid, give a warning*/
      else {

        errorOccured(16);
      }
    }

    /*if employee::operationNumberInMenu was 4, then we want create account for
     * a client:*/
    else if (this->myBank.getEmployee().getOperationNumberInMenu() == 4) {

      /*check if national code is valid or not, find the client and save its
       * index into Employee::indexOfClient:*/
      if (myBank.findClientByNationalCode(
              this->ui->lineEdit_Employee_enter_text->text())) {

        /*client is found set its info on screen:*/
        this->ui->textBrowser_employee_show_info->setText(
            this->myBank.getEmployee().showClientInfo(
                this->myBank.getVectorOfClients()));

        /*give a messege to enter initial amount:*/
        QMessageBox::about(this, "Alice Bank", "Enter initial amount!");

        /*set line edit:*/
        this->ui->lineEdit_Employee_enter_text->setText("Enter initail amount");

        /*set the operation to 5:*/
        this->myBank.getEmployeeByReference().setOperationNumberInMenu(5);

      }
      /*national code was not valid, give a warning:*/
      else {

        errorOccured(16);
      }
    }

    /*if employee::operationNumberInMenu was 5, then we want enter initail
     * amount for a new account:*/
    else if (this->myBank.getEmployee().getOperationNumberInMenu() == 5) {

      /*check if initail amount is less than 50000$ */
      if (this->ui->lineEdit_Employee_enter_text->text().toLongLong() < 50000) {
        errorOccured(17);
      }
      /*if there was no problem with inital amount:*/
      else {

        /*call the employee function that creates acount for client:*/
        this->myBank.getEmployeeByReference().createAccountForClient(
            myBank.getVectorOfClients(),
            ui->lineEdit_Employee_enter_text->text());

        /*hide buttons:*/
        this->ui->lineEdit_Employee_enter_text->hide();
        this->ui->pushButton_employee_go->hide();
        this->ui->pushButton_employee_enter_text->hide();

        /*print account info on screen:*/
        this->ui->textBrowser_employee_show_info->setText(
            this->myBank.getEmployee().showClientInfo(
                this->myBank.getVectorOfClients()));

        /*give a messege and say account added:*/
        QMessageBox::about(this, "Alice Bank", "Account created!");

        /*record the operation in report.txt:*/
        record(7);
      }
    }

    /*if operation number in menu == 8,then we want to delete an account:*/
    else if (this->myBank.getEmployee().getOperationNumberInMenu() == 8) {

      /*see if account number is valid or no:*/
      if (this->myBank.getEmployeeByReference().searchForAccount(
              myBank.getVectorOfClients(),
              this->ui->lineEdit_Employee_enter_text->text())) {

        /*account found , set its info on screen:*/
        this->ui->textBrowser_employee_show_info->setText(
            myBank.getClientByIndex(myBank.getEmployee().getClientIndex())
                .getAccount()
                .showInfoOfAccount());

        /*hide line edit and enter text buttons:*/
        this->ui->lineEdit_Employee_enter_text->hide();
        this->ui->pushButton_employee_enter_text->hide();

        /*show go buttons:*/
        this->ui->pushButton_employee_go->show();

      }

      /*account number is invalid:*/
      else {
        errorOccured(8);
      }
    }

    /*if operation number in menu == 9,then we want to show info of an
       employee:*/
    else if ((this->myBank.getEmployee().getOperationNumberInMenu() == 9) ||
             (this->myBank.getEmployee().getOperationNumberInMenu() == 10)) {

      /*see if user id is valid or no:*/
      if (this->myBank.getManagerByReference().findAnEmployee(
              this->ui->lineEdit_Employee_enter_text->text(),
              myBank.getVectorOfEmployee())) {

        /*employee found , set its info on screen:*/
        this->ui->textBrowser_employee_show_info->setText(
            myBank.getManagerByReference().showEmployeeInfo(
                myBank.getVectorOfEmployee()));

        /*if operation number == 10, then we want to delete this employee*/
        if (this->myBank.getEmployee().getOperationNumberInMenu() == 10) {

          /*make sure we are not deleting manager, if we are show a warning and
           * return to menu:*/
          if (myBank.getManagerByReference().getIndexOfEmployee() == 0) {

            /*this is manager! deleting opearation is not possible:*/
            this->errorOccured(25);

          }
          /*else this is not manager, we can delete it easily:*/
          else {
            /*we are deleting this employee,so, hide the enter button/enter text
             * line edit and show go button:*/
            this->ui->pushButton_employee_enter_text->hide();
            this->ui->pushButton_employee_go->show();
          }
        }

      }

      /*user id  is invalid:*/
      else {
        errorOccured(22);
      }
    }
  }
}

void AliceBank::on_pushButton_employee_go_clicked() {

  /*check in which operation button is pressed:*/

  /*Request for vacation hour:*/
  if (this->myBank.getEmployee().getOperationNumberInMenu() == 1) {

    /*call for the function to confirm adding vacation hours and also print
     * the result into textBrowser:*/
    this->ui->textBrowser_employee_show_info->setText(
        myBank.getEmployeeByReference().confirmIncreaseVacationHour());

    /*record the operation in report.txt:*/
    this->record(4);

  }
  /*request for over time work:*/
  else if (this->myBank.getEmployee().getOperationNumberInMenu() == 2) {

    /*call for the function that confirm increasing over time work hours and
     * also print the result into textBrowser:*/
    this->ui->textBrowser_employee_show_info->setText(
        this->myBank.getEmployeeByReference()
            .confirmIncreaseOverTimeWorkHour());

    /*record the operation in report.txt:*/
    this->record(6);
  }
  /*if equal to 8, then we wana delete account:*/
  else if (this->myBank.getEmployee().getOperationNumberInMenu() == 8) {

    /*delete account:*/

    /*if function return 1, it means that it deleted client,else, it means it
     * only deleted account of the client:*/
    if ((myBank.getEmployee().deleteAccount(
            myBank.getVectorOfClients(),
            this->ui->lineEdit_Employee_enter_text->text())) == 1) {

      /*client has been deleted, print this messege on text browser to inform
       * user:*/
      this->ui->textBrowser_employee_show_info->setText(
          "This account was the last account of this client\nTherefore client "
          "has been deleted!");

    }
    /*else means it deleted account:*/
    else {

      /*deleted account, show the new info of client:*/
      this->ui->textBrowser_employee_show_info->setText(
          this->myBank.getEmployee().showClientInfo(
              this->myBank.getVectorOfClients()));
    }

    /*record operation in report.txt:*/
    record(8);

    /*show messege operation was successful:*/
    QMessageBox::about(this, "Alice Bank", "Account deleted");
  }

  /*if number of operation in menu==10, then we want to delete employee:*/
  else if (this->myBank.getEmployee().getOperationNumberInMenu() == 10) {

    /*delete employee:*/
    myBank.getManagerByReference().deleteEmployee(myBank.getVectorOfEmployee());

    /*send a messege that employee deleted:*/
    QMessageBox::about(this, "Alice Bank", "Employee has been fired!");

    /*record operation in report.txt:*/
    record(10);

    /*get back to menu:*/
    this->on_pushButton_employee_back_to_employee_menu_clicked();
  }

  /*hide go button:*/
  this->ui->pushButton_employee_go->hide();
}

void AliceBank::on_pushButton_employee_overtime_request_clicked() {

  /*check if over time work are full or no:*/
  if (!(myBank.getEmployee().checkOverTimeWorkIsFull())) {

    /*set the data of over time work in ui::textBrowser*/
    this->ui->textBrowser_employee_show_info->setText(
        myBank.getEmployee().OverTimeHourData());

    /*hide menu buttons:*/
    this->hideMenuButtonsForEmployee();

    /*show non menu buttons:*/
    this->showNonMenuButtonsForEmployee();

    /*set messege enter hours into line edit:*/
    this->ui->lineEdit_Employee_enter_text->setText("Enter hour");

    /*save the number of operation menu into
     * employee::operationNumberInMenu::*/
    this->myBank.getEmployeeByReference().setOperationNumberInMenu(2);
  }

  /*over time work is full ,operation is not possible, give a warning:*/
  else {
    errorOccured(14);
  }
}

void AliceBank::on_pushButton_employee_show_pesonal_info_clicked() {

  /*set the personal info in ui::textBrowser*/
  this->ui->textBrowser_employee_show_info->setText(
      myBank.getEmployeeByReference().showPersonalInfo());

  /*hide menu buttons:*/
  this->hideMenuButtonsForEmployee();

  /*show textBrowser and back button:*/
  this->ui->textBrowser_employee_show_info->show();
  this->ui->pushButton_employee_back_to_employee_menu->show();
}

void AliceBank::on_pushButton_employee_show_client_info_clicked() {

  /*hide all menu buttons:*/
  this->hideMenuButtonsForEmployee();

  /*set the right messege on textBrowser:*/
  this->ui->textBrowser_employee_show_info->setText(
      "Please enter national code in line Edit.");

  /*set the messege t line edit:*/
  this->ui->lineEdit_Employee_enter_text->setText("Enter national code");

  /*show non menu buttons:*/
  this->showNonMenuButtonsForEmployee();

  /*make sure to save in which operation we are:*/
  this->myBank.getEmployeeByReference().setOperationNumberInMenu(3);
}

void AliceBank::on_pushButton_employee_create_account_for_a_client_clicked() {

  /*hide all menu buttons:*/
  this->hideMenuButtonsForEmployee();

  /*show back button:*/
  this->ui->pushButton_employee_back_to_employee_menu->show();

  /*show create account menu buttons:*/
  this->ui->pushButton_employee_create_account_already_client->show();
  this->ui->pushButton_employee_create_account_new_client->show();
}

void AliceBank::on_pushButton_employee_create_account_already_client_clicked() {
  /*hide buttons*/
  this->ui->pushButton_employee_create_account_already_client->hide();
  this->ui->pushButton_employee_create_account_new_client->hide();

  /*show textbrowser:*/
  this->showNonMenuButtonsForEmployee();

  /*set text browser:*/
  this->ui->textBrowser_employee_show_info->setText(
      "Enter client national code");

  /*set line edit:*/
  this->ui->lineEdit_Employee_enter_text->setText("Enter client national code");

  /*set operation menu number:*/
  this->myBank.getEmployeeByReference().setOperationNumberInMenu(4);
}

void AliceBank::on_pushButton_employee_create_account_new_client_clicked() {

  /*show new client widget:*/
  this->ui->widget_employee_new_client->show();

  /*clear all line edits:*/
  this->clearLineEditsNewClientWidget();

  /*show national code buttons:*/
  this->ui->label_employee_new_account_new_client_national_code->show();
  this->ui->lineEdit_employee_new_account_new_client_national_code->show();

  /*hide info buttons:*/
  this->hideInfoButtonsClientWidget();

  /*set operation menu number:*/
  this->myBank.getEmployeeByReference().setOperationNumberInMenu(6);
}

void AliceBank::on_pushButton_employee_new_account_new_client_back_clicked() {
  this->clearLineEditsNewClientWidget();
  this->ui->widget_employee_new_client->hide();
}

void AliceBank::on_pushButton_employee_new_account_new_client_go_clicked() {

  /*first check on which operation we are in:*/

  /*if operation menu ==6, this means we wana check if national code is valid
   * for new client or no,if any client with this national code was found,then
   * national code is repeated and we already have a client with this national
   * code:*/
  if (myBank.getEmployee().getOperationNumberInMenu() == 6) {

    /*check if the line edit is empty or not, of yes give a warning:*/
    if (this->ui->lineEdit_employee_new_account_new_client_national_code
            ->text() == "") {
      errorOccured(9);
    }

    /*check if the entered QString in line edit is a number or no*/
    else if (!(this->myBank.checkNumber(
                 this->ui
                     ->lineEdit_employee_new_account_new_client_national_code
                     ->text()))) {
      errorOccured(7);
    }

    /*check if national code entered has 10 digits or no*/
    else if (this->ui->lineEdit_employee_new_account_new_client_national_code
                 ->text()
                 .size() != 10) {
      errorOccured(21);
    }

    /*now that there is nothing wrong with line edit, check if national code is
     * valid*/
    else if (this->myBank.findClientByNationalCode(
                 this->ui
                     ->lineEdit_employee_new_account_new_client_national_code
                     ->text())) {
      errorOccured(18);
    }
    /*this national code is for a new client:*/
    else {

      /*hide national code buttons:*/
      this->ui->label_employee_new_account_new_client_national_code->hide();
      this->ui->lineEdit_employee_new_account_new_client_national_code->hide();

      /*show info buttons:*/
      this->showInfoButtonsClientWidget();

      /*set opearion number in menu:*/
      this->myBank.getEmployeeByReference().setOperationNumberInMenu(7);
    }
  }

  /*if operation number in menu is 7,then we want to add a new client :*/
  else if (this->myBank.getEmployee().getOperationNumberInMenu() == 7) {

    /*check all line edits are valid or not:*/
    if (this->checkIfLineEditValidNewClient()) {

      /*all valid, create new account for our new client:*/
      this->myBank.getEmployeeByReference().createAccountForNewClient(
          myBank.getVectorOfClients(),
          ui->lineEdit_employee_new_account_new_client_national_code->text(),
          ui->lineEdit_employee_new_account_new_client_name->text(),
          ui->lineEdit_employee_new_account_new_client_last_name->text(),
          ui->lineEdit_employee_new_account_new_client_birth_year->text(),
          ui->lineEdit_employee_new_account_new_client_birth_month->text(),
          ui->lineEdit_employee_new_account_new_client_birth_day->text(),
          ui->lineEdit_employee_new_account_new_client_user_name->text(),
          ui->lineEdit_employee_new_account_new_client_password->text(),
          ui->lineEdit_employee_new_account_new_client_initial_amount->text());

      /*give a messege that new client and new account has been added:*/
      QMessageBox::about(this, "Alice Bank",
                         "New account for our new client has been created!");

      /*get out of this widget:*/
      this->ui->widget_employee_new_client->hide();

      /*hide those 2 buttons:*/
      this->ui->pushButton_employee_create_account_new_client->hide();
      this->ui->pushButton_employee_create_account_already_client->hide();

      /*show text Browser:*/
      this->ui->textBrowser_employee_show_info->show();

      /*set info of our new client on screen:*/
      this->ui->textBrowser_employee_show_info->setText(
          this->myBank.getEmployee().showClientInfo(
              this->myBank.getVectorOfClients()));
    }
  }
}

void AliceBank::on_pushButton_employee_delete_account_of_a_client_clicked() {

  /*hide menu buttons:*/
  this->hideMenuButtonsForEmployee();

  /*show non menu buttons:*/
  this->showNonMenuButtonsForEmployee();

  /*set the operation number in menu:*/
  this->myBank.getEmployeeByReference().setOperationNumberInMenu(8);

  /*set the text browser:*/
  this->ui->textBrowser_employee_show_info->setText(
      "Enter number of account you want to delete");

  /*set line edit:*/
  this->ui->lineEdit_Employee_enter_text->setText("Enter account number");
}

void AliceBank::on_pushButton_employee_show_employee_info_clicked() {

  /*hide menu buttons:*/
  this->hideMenuButtonsForEmployee();

  /*show non menu buttons:*/
  this->showNonMenuButtonsForEmployee();

  /*set textBrowser:*/
  this->ui->textBrowser_employee_show_info->setText(
      "Enter user id of the employee in line edit");

  /*set line edit:*/
  this->ui->lineEdit_Employee_enter_text->setText("Enter user ID");

  /*set the opeartion number in menu:*/
  this->myBank.getEmployeeByReference().setOperationNumberInMenu(9);
}

void AliceBank::on_pushButton_employee_hire_employee_clicked() {

  /*hide menu buttons:*/
  this->hideMenuButtonsForEmployee();

  /*show new employee widget:*/
  this->ui->widget_manager_hire_employee->show();

  /*clear line edits in widget :*/
  this->clearLineEditsHireEmployeeWidget();
}

void AliceBank::on_pushButton_manager_hire_employee_go_clicked() {
  /*first we should check all line edits to be filled valid:*/

  /*first check if line edits are filled:*/
  if ((this->ui->lineEdit_manager_hire_employee_userid->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_name->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_last_name->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_birth_year->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_birth_month->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_birth_day->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_user_name->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_password->text() == "") ||
      (this->ui->lineEdit_manager_hire_employee_salary->text() == ""))

  {
    /*not all of line edits are full: */
    errorOccured(9);
  }

  /*check if userid/birth date/salary line edits are not filled with number:*/
  else if (!(myBank.checkNumber(
                 ui->lineEdit_manager_hire_employee_userid->text()) &&
             myBank.checkNumber(
                 ui->lineEdit_manager_hire_employee_birth_year->text()) &&
             myBank.checkNumber(
                 ui->lineEdit_manager_hire_employee_birth_month->text()) &&
             myBank.checkNumber(
                 ui->lineEdit_manager_hire_employee_birth_day->text()) &&
             myBank.checkNumber(
                 ui->lineEdit_manager_hire_employee_salary->text()))) {

    /*one of these or more is not filled with number:*/
    errorOccured(23);
  }

  /*check if user id has 3 digits:*/
  else if (ui->lineEdit_manager_hire_employee_userid->text().size() != 3) {

    /*user id does not have 3 digit:*/
    errorOccured(24);
  }

  /*check if user id is valid:*/
  else if (myBank.getManagerByReference().findAnEmployee(
               ui->lineEdit_manager_hire_employee_userid->text(),
               myBank.getVectorOfEmployee())) {

    /*employee with such user id found:*/
    errorOccured(22);
  }

  /*check if birth date is valid or not:*/
  else if (!(QDate::isValid(
               ui->lineEdit_manager_hire_employee_birth_year->text().toInt(),
               ui->lineEdit_manager_hire_employee_birth_month->text().toInt(),
               ui->lineEdit_manager_hire_employee_birth_day->text().toInt()))) {

    errorOccured(19);

  }

  /*check if user name and password is valid or no, there should not be any
   * client or employee with this user name and password:*/
  else if (this->myBank.searchForPasswordAndUserName(
               this->ui->lineEdit_manager_hire_employee_user_name->text(),
               this->ui->lineEdit_manager_hire_employee_password->text())) {

    errorOccured(3);
  }

  /*now that there is no problem with inputs, hire this employee:*/
  else {

    /*hire the employee:*/
    this->myBank.getManagerByReference().hireEmployee(
        myBank.getVectorOfEmployee(),
        this->ui->lineEdit_manager_hire_employee_userid->text(),
        this->ui->lineEdit_manager_hire_employee_name->text(),
        this->ui->lineEdit_manager_hire_employee_last_name->text(),
        this->ui->lineEdit_manager_hire_employee_birth_year->text(),
        this->ui->lineEdit_manager_hire_employee_birth_month->text(),
        this->ui->lineEdit_manager_hire_employee_birth_day->text(),
        this->ui->lineEdit_manager_hire_employee_user_name->text(),
        this->ui->lineEdit_manager_hire_employee_password->text(),
        this->ui->lineEdit_manager_hire_employee_salary->text());

    /*hide this widget:*/
    this->ui->widget_manager_hire_employee->hide();

    /*show back button and text browser:*/
    this->ui->textBrowser_employee_show_info->show();
    this->ui->pushButton_employee_back_to_employee_menu->show();

    /*set info of this employee in text browser:*/
    this->ui->textBrowser_employee_show_info->setText(
        myBank.getManagerByReference().showEmployeeInfo(
            myBank.getVectorOfEmployee()));

    /*record in report.txt:*/
    record(9);

    /*give a messege that employee hired:*/
    QMessageBox::about(this, "Alice Bank", "New employee hired!");
  }
}

void AliceBank::on_pushButton_manager_hire_employee_back_clicked() {

  /*clear line edits:*/
  this->clearLineEditsHireEmployeeWidget();

  /*hide widget:*/
  this->ui->widget_manager_hire_employee->hide();

  /*show menu buttons:*/
  this->showMenuButtonsForEmployee();
}

void AliceBank::on_pushButton_employee_fire_employee_clicked() {
  /*hide menu buttons:*/
  this->hideMenuButtonsForEmployee();

  /*show non menu buttons:*/
  this->showNonMenuButtonsForEmployee();

  /*set line edit:*/
  this->ui->lineEdit_Employee_enter_text->setText("Enter userID");

  /*set text browser:*/
  this->ui->textBrowser_employee_show_info->setText(
      "Enter user id of the employee you want to fire");

  /*set operation number in menu:*/
  this->myBank.getEmployeeByReference().setOperationNumberInMenu(10);
}
