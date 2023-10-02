#ifndef USERLOGINMODEL_H
#define USERLOGINMODEL_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <doctor_main.h>
#include <QMessageBox>
#include <databaseController.h>

//This is the model which will inlcude functions related to UserLogin Table.
//It will be used while logging into the system, adding new users to the system, updating or deleting users from the system.
//It will communicate with table:UserLogin in database and pass the results to view.

class UserLoginModel {

public :

    void getLoginResults(QString userID,QString userPassword, bool &loginStatus, QString &userRole)
    {
        //Initia database connection and assign it to boolean
        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        bool userIdExist = false;
        loginStatus = false;
        userRole = "Unknown";

        //If database is connected, check if userID exist
        if (databaseConnected){

            checkIDExistence(userID, userPassword, loginStatus, userRole);

        }
        else {

            Msgbox.setText("Database connection error");
            Msgbox.exec();
            loginStatus = false;

        }
        dc.closeDatabase();
    }


    QStringList getLogInUserDoctors(QString userID)
    {
        //Initia database connection and assign it to boolean
        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        QStringList loginDoctorID;

        //If database is connected, check if userID exist
        if (databaseConnected){

            QSqlQuery query;
            QString queryString = "SELECT * FROM UserDoctors where UserID = '" + userID + "'";
            query.prepare(queryString);
            query.exec();

            while (query.next()) {
                loginDoctorID.append(query.value(0).toString());
                loginDoctorID.append(query.value(1).toString());
                loginDoctorID.append(query.value(5).toString());
                loginDoctorID.append(query.value(7).toString());
                loginDoctorID.append(query.value(8).toString());
                loginDoctorID.append(query.value(9).toString());

            }

        }
        else {



        }
        dc.closeDatabase();
        return loginDoctorID;
    }


    QStringList getLogInUserHospitalAdmin(QString userID)
    {
        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        QStringList loginHospitalAdminID;

        if (databaseConnected){

            QSqlQuery query;
            QString queryString = "SELECT * FROM UserHospitalAdmins where UserId = '" + userID + "'";
            query.prepare(queryString);
            query.exec();

            while (query.next()) {
                loginHospitalAdminID.append(query.value(9).toString());
            }
            QString hospitalID = loginHospitalAdminID[0];
            QString queryString2 = "SELECT * FROM Hospitals where ID = '" + hospitalID + "'";

            query.prepare(queryString2);
            query.exec();

            while (query.next()) {
                loginHospitalAdminID.append(query.value(1).toString());
            }

        }
        else {



        }
        dc.closeDatabase();
        return loginHospitalAdminID;
    }




    void checkIDPasswordMatched(QString userID, QString userPassword, bool &loginStatus, QString &userRole)
    {

        //If user and password matches, loginStatus becomes true
        if (userIDFromDB == userID && passwordFromDB == userPassword){
            loginStatus = true;
            userRole = userTypeFromDB;
            qDebug() << "User and pass is correct";
        }
        else{
            Msgbox.setText("User name and password is NOT correct.");
            Msgbox.exec();
            loginStatus = false;
        }

    }


    void checkIDExistence(QString userID,QString userPassword, bool &loginStatus, QString &userRole)
    {

        QSqlQuery query;
        QString queryString = "SELECT * FROM UserLogin where LoginID = '" + userID + "'";
        query.prepare(queryString);
        //If query returns a value, then userID exist
        query.exec();
        bool userIdExist = query.first();
        if(userIdExist){
            userIDFromDB = query.value("LoginID").toString();
            passwordFromDB = query.value("Password").toString();
            userTypeFromDB = query.value("Role").toString();

            checkIDPasswordMatched(userID, userPassword, loginStatus, userRole);
        }
        else{
            Msgbox.setText("UserID doesn't exist. Check your User ID. Or check with your system admin.");
            Msgbox.exec();
            loginStatus = false;
        }

    }


    private:
    QString userIDFromDB;
    QString passwordFromDB;
    QString userTypeFromDB;
    QMessageBox Msgbox;
};



#endif // USERLOGINMODEL_H
