#ifndef HOSPITALADMINMODEL_H
#define HOSPITALADMINMODEL_H
#include <QMessageBox>
#include <databaseController.h>
#include <iostream>

class hospitalAdminModel {
public:
    void queryHospitalAdmin(QString& firstName, QString lastname, QString& queryResult, QString& queryString, QString ID, QString Email){

        QMessageBox Msgbox;
        queryResult = "";
        queryString = "";
        QString queryStringPart2;

        if (firstName.isEmpty()){
            queryResult = "<p style=\"color:red\">first Name is required!</p>";
        }
        else{
            databaseController dc;
            bool databaseConnected = dc.initDatabase();

            if (databaseConnected){
                QSqlQuery query;
                queryString = "SELECT * FROM UserHospitalAdmins WHERE FirstName = '" + firstName + "'";
                queryStringPart2 = queryStringSecondPart(ID, lastname, Email);
                queryString = queryString + queryStringPart2;
                qDebug() << queryString;
                qDebug() << "after part2";
                query.prepare(queryString);
                //If query returns a value, then hospital exists;
                query.exec();
                bool userIdExist = query.first();
                if (!userIdExist){
                    queryResult = "<p style=\"color:red\">No matching admin Found!</p>";
                }
            }
             qDebug() << "working";
        }
    }

    QString queryStringSecondPart(QString ID = "", QString lastname ="", QString Email=""){
        QString queryStringPart2 = "";
        if(!ID.isEmpty())
        {
            queryStringPart2 += " AND UserId = '" + ID +"'";
        }
        if(!lastname.isEmpty())
        {
            queryStringPart2 += " AND LastName = '" + lastname +"'";
        }
        if(!Email.isEmpty())
        {
             queryStringPart2 += "AND EmailId = '" + Email + "'";
        }
        qDebug() << "before part2";
        qDebug() << queryStringPart2;
        return queryStringPart2;
    }

    QString addHospitalAdmin(QString fName, QString mName, QString lName, QString Email, QString Mphone, QString Ophone, QString ID, QString password){
        QString addHospitalQueryString;
        QString addHospitalQueryStringset;
        QString addHospitalResult = "";
        databaseController dc;
        bool databaseConnected = dc.initDatabase();

        if (databaseConnected){
            QSqlQuery query;
            addHospitalQueryStringset = addHospitalAdminConstructor(fName, mName, lName, Email, Mphone, Ophone, ID, password);
            //qDebug << "All information are provided";
            qDebug()<< "addAdmin";
            qDebug() << addHospitalQueryStringset;
            query.prepare(addHospitalQueryStringset);
            query.exec();
            addHospitalResult = "<p style=\"color:green\">admin is sucessfully added!</p>";
        }
    return addHospitalResult;
    }

    QString addHospitalAdminConstructor(QString fName, QString mName, QString lName, QString Email, QString Mphone, QString Ophone, QString ID, QString password){
        QString queryAddHospitalColumns = "INSERT INTO UserHospitalAdmins (FirstName, MiddleName, LastName, UserId, EmailId, OfficePhone, MobilePhone, HospitalID)";
        QString queryAddHospitalValues = " VALUES ('" + fName + "', '" + mName + "', '" + lName + "', '" + ID + "', '" + Email + "', '"  + Ophone + "', '" + Mphone + "', '" + "')";
        QString AddHospitalString = queryAddHospitalColumns + queryAddHospitalValues;
        return AddHospitalString;
    }

};
#endif // HOSPITALADMINMODEL_H
