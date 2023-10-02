#ifndef USERSYSTEMADMINMODEL_H
#define USERSYSTEMADMINMODEL_H

#include <QMessageBox>
#include <databaseController.h>
#include <iostream>
#include "CheckValidEmail.h"
#include "CheckValidPassword.h"
#include "CheckValidPhone.h"

class UserSystemAdminModel {
public:
    void queryUserAdmin(QString &HospitalName, QString& HospitalID, QString& queryResult, QString& queryString){

        QMessageBox Msgbox;
        queryResult = "";
        queryString = "";
        QString queryStringPart2;

        if (HospitalName.isEmpty()){
            queryResult = "<p style=\"color:red\">HospitalName is required!</p>";
        }
        else{
            databaseController dc;
            bool databaseConnected = dc.initDatabase();

            if (databaseConnected){
                QSqlQuery query;
                queryString = "SELECT ID, HospitalName, AddressStreet1, AddressStreet2, AddressCity, AddressState, AddressZip, Country FROM Hospitals WHERE HospitalName = '" + HospitalName + "'";
                queryStringPart2 = queryStringSecondPart(HospitalID);
                queryString += queryStringPart2;

                query.prepare(queryString);
                //If query returns a value, then hospital exists;
                query.exec();
                bool userIdExist = query.first();
                if (!userIdExist){
                    queryResult = "<p style=\"color:red\">No matching Hospital Found!</p>";
                }
            }

        }
    }

    QString queryStringSecondPart(QString HospitalID = ""){
        QString queryPart2 = "";
        if(!HospitalID.isEmpty()){
            queryPart2 += "AND ID  = '" + HospitalID + "'";
        }
        return queryPart2;
    }

    QString getNewHospitalID(){
        QString newHospitalID;
        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        if (databaseConnected){

            QSqlQuery query;
            QString queryString = "SELECT ID FROM drstrangev0.Hospitals ORDER BY id DESC LIMIT 1";
            query.prepare(queryString);
            query.exec();

            while (query.next()) {
                newHospitalID.append(query.value(0).toString());
            }

        }

        return newHospitalID;
    }

    QString addHospital(QString HospitalName, QString HospitalAdd1, QString HospitalAdd2, QString HospitalCity, QString HospitalState, QString HospitalZip, QString HospitalCountry){
        QString addHospitalQueryString;
        QString addHospitalQueryStringset;
        QString addHospitalResult = "";
        databaseController dc;
        bool databaseConnected;
        databaseConnected = dc.initDatabase();
        if (HospitalName.isEmpty() && HospitalAdd1.isEmpty() && HospitalCity.isEmpty() && HospitalState.isEmpty() && HospitalZip.isEmpty() && HospitalCountry.isEmpty()){
            addHospitalResult = "<p style=\"color:red\">Please enter at least one Entry!</p>";
        }
        else if (HospitalName.isEmpty()){
            addHospitalResult = "<p style=\"color:#EF2F2F\">Hospital Name cannot be empty!</p>";
        }
        else if (HospitalAdd1.isEmpty()){
            addHospitalResult = "<p style=\"color:#EF2F2F\">Hospital Address cannot be empty!</p>";
        }
        else if (HospitalCity.isEmpty()){
            addHospitalResult = "<p style=\"color:#EF2F2F\">Hospital City cannot be empty!</p>";
        }
        else if (HospitalState.isEmpty()){
            addHospitalResult = "<p style=\"color:#EF2F2F\">Hospital State cannot be empty!</p>";
        }
        else if (HospitalZip.isEmpty()){
            addHospitalResult = "<p style=\"color:#EF2F2F\">Hospital ZipCode cannot be empty!</p>";
        }
        else if (HospitalCountry.isEmpty()){
            addHospitalResult = "<p style=\"color:#EF2F2F\">Hospital Country cannot be empty!</p>";
        }
        else {
            QSqlQuery query;
            addHospitalQueryStringset = addHospitalConstructor(HospitalName, HospitalAdd1, HospitalAdd2, HospitalCity, HospitalState, HospitalZip, HospitalCountry);
            //qDebug << "All information are provided";
            query.prepare(addHospitalQueryStringset);
            query.exec();
            addHospitalResult = "<p style=\"color:green\">Hospital is sucessfully added!</p>";
        }
    return addHospitalResult;
    }

    QString addHospitalConstructor(QString HospitalName, QString HospitalAdd1, QString HospitalAdd2, QString HospitalCity, QString HospitalState, QString HospitalZip, QString HospitalCountry){
        QString queryAddHospitalColumns = "INSERT INTO Hospitals (HospitalName, AddressStreet1, AddressStreet2, AddressCity, AddressState, AddressZip, Country)";
        QString queryAddHospitalValues = " VALUES ('" + HospitalName + "', '" + HospitalAdd1 + "', '" + HospitalAdd2 + "', '" + HospitalCity + "', '" + HospitalState + "', '" + HospitalZip + "', '" + HospitalCountry + "')";
        QString AddHospitalString = queryAddHospitalColumns + queryAddHospitalValues;
        return AddHospitalString;
    }



    QString addHospitalAdmin(QString FirstName, QString MiddleName, QString LastName, QString UserId, QString EmailId,QString OfficePhone, QString MobilePhone, QString HospitalID, QString Password){
        QString addHospitalAdminQuery;
        QString addHospitalAdminResult = "";
        QString addUserLoginString;
        QString addAppointmentResult;
        QString userRole = "HospitalAdmin";
        QString userStatus = "1";
        CheckValid ck;
        CheckValidPass ps;
        checkphone cp;
        databaseController dc;
        //bool databaseConnected = dc.initDatabase();
        if (FirstName.isEmpty() && LastName.isEmpty() && UserId.isEmpty() && EmailId.isEmpty() && OfficePhone.isEmpty() && MobilePhone.isEmpty() && Password.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">Pleaese enter all the required information!</p>";
        }
        else if (FirstName.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">First Name cannot be empty!</p>";
        }
        else if (LastName.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">Last Name cannot be empty!</p>";
        }
        else if (UserId.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">User ID cannot be empty!</p>";
        }
        else if (EmailId.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">Email cannot be empty!</p>";
        }
        else if (OfficePhone.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">Office phone number cannot be empty!</p>";
        }
        else if (MobilePhone.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">Mobile phone number cannot be empty!</p>";
        }
        else if (Password.isEmpty()){
            addHospitalAdminResult = "<p style=\"color:#EF2F2F\">Temporary password cannot be empty!</p>";
        }
        else if (Password.length() < 9){
            addHospitalAdminResult = "<p style=\"color:#00D2FF\">The length of your password has to be at least 9 characters!</p>";
        }
        else if (!ck.is_valid(EmailId)){
            addHospitalAdminResult = "<p style=\"color:#00D2FF\">Please enter a valid email address!</p>";
        }
        else if (!ps.checkvalid(Password)){
            addHospitalAdminResult = "<p style=\"color:red\">Please enter a valid password!</p>";
        }
        else if (!cp.check(MobilePhone) || !cp.check(OfficePhone)){
            addHospitalAdminResult = "<p style=\"color:red\">Please enter a valid phone number with format XXX-XXX-XXXX</p>";
        }
        else{
            QSqlQuery query;
            addHospitalAdminQuery = addHospitalAdminConstructor(FirstName, MiddleName, LastName, UserId, EmailId, OfficePhone, MobilePhone, HospitalID);
            query.prepare(addHospitalAdminQuery);
            query.exec();
            QString queryAddLoginUserColumns = "INSERT INTO UserLogin (Role, Active, EmailID, LoginID, Password)";
            QString queryAddLoginUserValues = " VALUES ('" + userRole + "', '" + userStatus + "', '" + EmailId + "', '" + UserId + "', '" + Password + "')";
            addUserLoginString = queryAddLoginUserColumns + queryAddLoginUserValues;
            qDebug() << addUserLoginString;


            query.prepare(addUserLoginString);
            query.exec();


            addHospitalAdminResult = "<p style=\"color:green\">Hospital Admin is sucessfully added!</p>";
        }
        return addHospitalAdminResult;
    }

    QString addHospitalAdminConstructor(QString FirstName, QString MiddleName, QString LastName, QString UserId, QString EmailId,QString OfficePhone, QString MobilePhone, QString HospitalID){
        QString queryAddHospitalAdminCol = "INSERT INTO UserHospitalAdmins (FirstName, MiddleName, LastName, Role, UserId, EmailId, OfficePhone, MobilePhone, HospitalID)";
        QString queryAddHospitalAdminVal = "VALUES ('" + FirstName + "', '" + MiddleName + "','" + LastName + "','HospitalAdmin','" + UserId + "','" + EmailId + "','" + OfficePhone + "','" + MobilePhone + "','" + HospitalID + "')";
        return queryAddHospitalAdminCol+queryAddHospitalAdminVal;
    }

};



#endif // USERSYSTEMADMINMODEL_H
