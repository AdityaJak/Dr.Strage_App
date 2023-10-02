#ifndef DOCTORMODEL_H
#define DOCTORMODEL_H
#include <QMessageBox>
#include <databaseController.h>
#include <iostream>

class DoctorModel {
public:
    void queryDoctor(QString firstName, QString lastName, QString& queryResult, QString& queryString, QString ID, QString Email){

        QMessageBox Msgbox;
        queryResult = "";
        queryString = "";
        QString queryStringPart2;

        if (firstName.isEmpty() && lastName.isEmpty() && ID.isEmpty() && Email.isEmpty()){
            queryResult = "<p style=\"color:red\">At least one field is required!</p>";
        }
        else{
            databaseController dc;
            bool databaseConnected = dc.initDatabase();

            if (databaseConnected){
                QSqlQuery query;
                queryString = "SELECT NameParts_Family, NameParts_Given, UserID, EmailID FROM UserDoctors WHERE NameParts_Given = '" + firstName + "'" + " AND NameParts_Family = '" + lastName + "'";
                queryStringPart2 = queryStringSecondPart(ID, lastName, Email);
                queryString += queryStringPart2;

                query.prepare(queryString);
                //If query returns a value, then hospital exists;
                query.exec();

                bool userIdExist = query.first();
                if (!userIdExist){
                    queryResult = "<p style=\"color:red\">No matching doctor Found!</p>";
                }
            }

        }
    }

    QString queryStringSecondPart(QString ID = "", QString lastname = "", QString Email = ""){
        QString queryStringPart2 = "";
        if(!ID.isEmpty())
        {
            queryStringPart2 += " AND UserID = '" + ID +"'";
        }
        if(!lastname.isEmpty())
        {
            queryStringPart2 += " AND NameParts_Family = '" + lastname +"'";
        }
        if(!Email.isEmpty())
        {
             queryStringPart2 += "AND EmailID = '" + Email + "'";
        }


        return queryStringPart2;
    }
    //Adding doctor user login into the database
    void addUserLogin(QString Email, QString userID, QString password) {
        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        QString userRole = "Doctor";

        QString userStatus = "1";
        QString queryAddLoginUserColumns = "INSERT INTO UserLogin (Role, Active, EmailID, LoginID, Password)";
        QString queryAddLoginUserValues = " VALUES ('" + userRole + "', '" + userStatus + "', '" + Email + "', '" + userID + "', '" + password + "')";
        QString addUserLoginString = queryAddLoginUserColumns + queryAddLoginUserValues;
        QSqlQuery query;
        qDebug() << addUserLoginString;

        query.prepare(addUserLoginString);
        query.exec();

    }
    //Adding a certain doctor
    QString addDoctor(QString& addDoctorResultLabel, QString Hospitalid, QString LanguageCommute, QString userID, QString lastName, QString firstName, QString ZipCode, QString State, QString City, QString Addline1, QString Email, QString mobilePhone, QString officePhone = "", QString ProviderID = "", QString Roles = "", QString Specialty = "", QString type = "", QString MiddleName = "", QString Addline2 = "",  QString addressCountry = ""){
        QString addDoctorResult;
        QString addDoctorQueryStringset;
        databaseController dc;
        bool databaseConnected = dc.initDatabase();

        if (databaseConnected){
            QSqlQuery query;
            addDoctorQueryStringset = addDoctorConstructor(Hospitalid, LanguageCommute, userID, lastName, firstName, ZipCode, State, City, Addline1, Email, mobilePhone, officePhone, ProviderID, Roles, Specialty, type, MiddleName, Addline2, addressCountry);
            //qDebug << "All required information are provided";
            query.prepare(addDoctorQueryStringset);
            qDebug() << "test addHospital";
            query.exec();
            qDebug() << addDoctorQueryStringset;
            addDoctorResult = "<p style=\"color:green\">Doctor is sucessfully added!</p>";
        }
        return addDoctorResult;
    }

    QString addDoctorConstructor(QString Hospitalid, QString LanguageCommute, QString userID, QString lastName, QString firstName, QString ZipCode, QString State, QString City, QString Addline1, QString Email, QString mobilePhone, QString officePhone = "", QString ProviderID = "", QString Roles = "", QString Specialty = "", QString type = "", QString MiddleName = "", QString Addline2 = "", QString addressCountry = ""){
        QString queryAddDoctorColumns = "INSERT INTO UserDoctors (HospitalID, LanguageCommunication, UserID, NameParts_Family, NameParts_Given, AddressCountry, AddressZipCode, AddressState, AddressCity, AddressStreet1, EmailID, MobilePhone";
        QString queryAddDoctorValues = " VALUES ('" + Hospitalid + "', '" + LanguageCommute + "', '" + userID + "', '" + lastName + "', '" + firstName + "', '" + addressCountry + "', '" + ZipCode + "', '" + State + "', '" + City + "', '" + Addline1 + "', '" + Email + "', '" + mobilePhone + "'";
        if(!ProviderID.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", ProviderID";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + ProviderID + "'";
        }

        if(!Roles.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", Roles";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + Roles + "'";
        }

        if(!addressCountry.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", AddressCountry";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + addressCountry + "'";
        }

        if(!Specialty.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", Specialty";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + Specialty + "'";
        }

        if(!type.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", Type";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + type + "'";
        }

        if(!MiddleName.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", NameParts_Middle";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + MiddleName + "'";
        }

        if(!Addline2.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", Addline2";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + Addline2 + "'";
        }

        if(!officePhone.isEmpty()){
           queryAddDoctorColumns = queryAddDoctorColumns + ", OfficePhone";
           queryAddDoctorValues = queryAddDoctorValues + ", '" + officePhone + "'";
        }

        queryAddDoctorColumns = queryAddDoctorColumns + ")";
        queryAddDoctorValues = queryAddDoctorValues + ")";

        QString AddDoctorString = queryAddDoctorColumns + queryAddDoctorValues;
        return AddDoctorString;
    }

};
#endif // DOCTORMODEL_H
