#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <doctor_main.h>
#include <doctormainwindow.h>
#include <hospitaladminmain.h>
#include <systemadminmain.h>
#include <databaseController.h>
#include <UserLoginModel.h>
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}

// Log in button
void MainWindow::on_loginButton_clicked()
{
    QString loginID = ui->userIDText->text();
    QString password = ui->passwordText->text();
    QString userRoleTemp = "";
    bool loginResultTemp;
    QString userRole = "";
    bool loginResult;
    QStringList loginUserData;
    loginUserData.append(loginID);

    UserLoginModel ulm;
    ulm.getLoginResults(loginID, password, loginResultTemp, userRoleTemp);
    userRole = userRoleTemp;
    loginResult = loginResultTemp;

    if(loginResult){
        //Here routing the user based on the user type.
        if(userRoleTemp=="Doctor"){
            hide();
            if(!doctor_main_window)
               {
                  doctor_main_window = new DoctorMainWindow(this);
               }
             doctor_main_window->setWindowState(Qt::WindowMaximized);
             doctor_main_window->show();
             connect(this, SIGNAL(sendData(QStringList)), doctor_main_window, SLOT(receiveData(QStringList)));
             emit sendData(loginUserData);
           }

        if(userRoleTemp=="HospitalAdmin"){
            hide();

            if(!hospitalAdminMain_window)
               {
                  hospitalAdminMain_window = new hospitalAdminMain(this);
               }
             hospitalAdminMain_window->setWindowState(Qt::WindowMaximized);
             hospitalAdminMain_window->show();
             connect(this, SIGNAL(sendData(QStringList)), hospitalAdminMain_window, SLOT(receiveData(QStringList)));
             emit sendData(loginUserData);

           }

        if(userRoleTemp=="Admin"){
            hide();

            if(!systemAdminMain_window)
               {
                  systemAdminMain_window = new systemAdminMain(this);
               }
             systemAdminMain_window->setWindowState(Qt::WindowMaximized);
             systemAdminMain_window->show();
             connect(this, SIGNAL(sendData(QStringList)), systemAdminMain_window, SLOT(receiveData(QStringList)));
             emit sendData(loginUserData);
           }

    }
}

void MainWindow::ClearUsernamePassword()
{
    ui->userIDText->clear();
    ui->passwordText->clear();
}





void MainWindow::on_pushButton_clicked()
{
    QMessageBox Msgbox;
    Msgbox.setText("If you are a doctor and you need assistance:\n Please check with your hospital administrator.\n \n If you are a Hospital Administrator and need assistance: \nPlease contact your account manager or create a ticket at support@drstrange.com ");
    Msgbox.exec();
}

