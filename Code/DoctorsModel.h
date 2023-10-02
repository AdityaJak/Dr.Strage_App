#ifndef DOCTORSMODEL_H
#define DOCTORSMODEL_H
#include <iostream>
#include <QMessageBox>
#include <databaseController.h>



#endif // DOCTORSMODEL_H

class DoctorsModel {

public:
    void queryDoctor(QString &HospitalName, QString &Country, QString &queryResult, QString &queryString, QString &NameParts_Family, QString &NameParts_Given)
    {
        QMessageBox Msgbox;
        queryResult = "";
        queryString = "";
        //check if first and last name is provided or not
        if (NameParts_Family.isEmpty() || NameParts_Given.isEmpty()){
            queryResult = "<p style=\"color:red\">Doctor First and Last Name is required!</p>";
        }
        else{
            databaseController dc;
            bool databaseConnected = dc.initDatabase();

            if (databaseConnected){
                QSqlQuery query;
                queryString = "SELECT HospitalName, AddressCountry, NameParts_Family, NameParts_Given FROM UserDoctors WHERE HospitalName = '" + HospitalName + "'" + " AND AddressCountry = '" + Country + "'" + " AND NameParts_Family = '"
                        + NameParts_Family + "'" + "AND NameParts_Given = '" + NameParts_Given + "'";

                query.prepare(queryString);
                query.exec();
                if (!query.first()){
                    queryResult = "<p style=\"color:red\">No matching Doctor was found!</p>";
                }
            }
        qDebug() << "First and last name are provided";
        }
    }
    //
    QString addDoctor(QString HospitalID, QString UserID, QString FirstName, QString LastName, QString HospitalName, QString roles, QString LanguageCommute = ""){
        QString addDoctorQueryString;
        QString addDoctorQuerySet;

        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        if (databaseConnected){
            QSqlQuery query;

            qDebug() << "Hospital ID and User ID are provided";
            query.prepare(addDoctorQuerySet);
            query.exec();
            //addDoctorResult = "<p style=\"color:green\">Patient is added!</p>";
        }
    //return addDoctorResult;
    }

    QString queryAddPatientStringConstructor(QString HospitalID, QString UserID, QString FamilyName, QString GivenName, QString LanguageCommute, QString MartialStatus = "", QString Organization = "", QString ProviderID = "", QString Race = "",QString ReligiousAff = "",QString Roles= "",QString Specialty = "", QString SubSpecialty = "",QString Type = "",QString MiddleName = "", QString Prefix = "", QString Suffix = "", QString HospitalName = "", QString AddressCountry = "", QString AddressZipcode = "", QString AddressState = "", QString City = "", QString Addressline2 = "", QString Addressline1 = "", QString EmailID = "", QString Officephone = "", QString MobilePhone = ""){
        QString queryAddDoctorColumns = "INSERT INTO UserDoctors (HospitalID, LanguageCommunication, UserID, NameParts_Family, NameParts_Given";
        QString queryAddDoctorValues = " VALUES ('" + HospitalID + "', '" + LanguageCommute + "', '" + UserID + "', '" + FamilyName + "', '" + GivenName + "'";
        QString queryAddDoctorString;
        queryAddDoctorColumns += ")";
        queryAddDoctorValues += ")";
        queryAddDoctorString = queryAddDoctorColumns + queryAddDoctorValues;
        return queryAddDoctorString;

    }
};
