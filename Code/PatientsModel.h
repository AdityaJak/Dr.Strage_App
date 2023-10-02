#ifndef PATIENTSMODEL_H
#define PATIENTSMODEL_H


#include <iostream>
#include <QMessageBox>
#include <databaseController.h>
#include "CheckValidPhone.h"
#include "CheckValidEmail.h"

//This is the model which will inlcude functions related to UserLogin Table.
//It will be used while logging into the system, adding new users to the system, updating or deleting users from the system.
//It will communicate with table:UserLogin in database and pass the results to view.

class PatientsModel {

public :

    void queryPatient(QString &firstName,QString &lastName, QString &queryResult, QString &queryString, QString SSN = "", QString DOB = "")
    {

        QMessageBox Msgbox;
        queryResult = "";
        queryString = "";
        QString queryStringPart2 = "";


        //check if first and last name is provided
        if (lastName.isEmpty() || firstName.isEmpty()){
         queryResult = "<p style=\"color:red\">First and Last Name is required!</p>";
        }

       if(!lastName.isEmpty() && !firstName.isEmpty()){

           databaseController dc;
           bool databaseConnected = dc.initDatabase();

           //If database is connected
           if (databaseConnected){
               QSqlQuery query;
               queryString = "SELECT ID, PatientName, PatientLastName, PatientDOB, PatientEmail, PatientMobilePhone FROM Patients WHERE PatientName = '" + firstName + "'" + " AND PatientLastName = '" + lastName + "'";
               queryStringPart2 = queryStringSecondPart(SSN,DOB);

               queryString = queryString + queryStringPart2;

               query.prepare(queryString);
               //If query returns a value, then userID exist
               query.exec();
               bool userIdExist = query.first();
               if(!userIdExist){
                   queryResult = "<p style=\"color:red\">No matching patient!</p>";
               }
           }


       qDebug() << "First and last name are provided";
       }

        //return queryResult;

    }


    QStringList queryPatientForUpdate(QString patientID)
    {

        QMessageBox Msgbox;
        QStringList queryResultList;
        //int patientIDInt = patientID.toInt();



           databaseController dc;
           bool databaseConnected = dc.initDatabase();

           //If database is connected
           if (databaseConnected){
               QSqlQuery query;
               QString queryString = "SELECT * FROM Patients WHERE ID = " + patientID;
               qDebug() << "First and last name are provided";
               query.prepare(queryString);
               //If query returns a value, then userID exist
               query.exec();

                while (query.next()) {
                    queryResultList.append(query.value(0).toString());
                    queryResultList.append(query.value(1).toString());
                    queryResultList.append(query.value(2).toString());
                    queryResultList.append(query.value(3).toString());
                    queryResultList.append(query.value(4).toString());
                    queryResultList.append(query.value(5).toString());
                    queryResultList.append(query.value(6).toString());
                    queryResultList.append(query.value(7).toString());
                    queryResultList.append(query.value(8).toString());
                    queryResultList.append(query.value(9).toString());
                    queryResultList.append(query.value(10).toString());
                    queryResultList.append(query.value(11).toString());
                    queryResultList.append(query.value(12).toString());
                    queryResultList.append(query.value(13).toString());
                    queryResultList.append(query.value(14).toString());
                    qDebug() << queryResultList;
               }


           }
        qDebug() << "First and last name are provided";

        return queryResultList;

    }



    void updatePatient(QString &ID,QString &firstName,QString &middleName,QString &lastName, QString &DOB,QString &SSN,QString &Email,QString &mobilePhone,QString &workPhone,QString &homePhone,QString &street1,QString &street2,QString &city,QString &state,QString &zip,QString &queryResult)
    {

        queryResult = "";
        QString queryString = "";
        checkphone cp;
        CheckValid cv;

        //check if first and last name is provided
        if (lastName.isEmpty() || firstName.isEmpty()){
            queryResult = "<p style=\"color:red\">First and Last Name is required!</p>";
        }
        else if (mobilePhone.isEmpty()){
            queryResult = "<p style=\"color:red\">Please Enter your phone number!</p>";
        }
        else if (!cp.check(mobilePhone) || !cp.check(workPhone)){
            queryResult = "<p style=\"color:red\">Please Enter a valid phone number with format XXX-XXX-XXXX!</p>";
        }
        else if (!cv.is_valid(Email)){
            queryResult = "<p style=\"color:red\">Please Enter a valid email address!</p>";
        }
        else{
            databaseController dc;
            bool databaseConnected = dc.initDatabase();

            //If database is connected
            if (databaseConnected){
                QSqlQuery query;
                queryString = "UPDATE Patients SET PatientAddressState='" + state +"',PatientHomePhone='"+homePhone+"',PatientName='"+firstName+"',PatientWorkPhone='"+workPhone+"',PatientEmail='"+Email+"',PatientMiddleName='"+middleName+"',PatientLastName='"+lastName+"',PatientMobilePhone='"+mobilePhone+"',PatientAddressZipCode='"+zip+"',PatientSSN='"+SSN+"',PatientDOB='"+DOB+"',PatientAddressStreet='"+street1+"',PatientAddressLine2='"+street2+"',PatientAddressCity='"+city+"' WHERE ID='" +ID +"'";
                query.prepare(queryString);
                query.exec();
                bool userIdExist = query.first();
                if(!userIdExist){
                    queryResult = "<p style=\"color:red\">No matching patient!</p>";
                }
            }


        qDebug() << "First and last name are provided";
        queryResult = "<p style=\"color:red\">Patient is added!</p>";
    }

    //return queryResult;
}


    QString queryStringSecondPart(QString SSN = "", QString DOB = ""){

        QString queryStringPart2 = "";

        if(SSN.isEmpty() && DOB.isEmpty()){
           queryStringPart2 = "";
        }

        if(!SSN.isEmpty() && DOB.isEmpty()){
            queryStringPart2 = " AND PatientSSN = '" + SSN +"'";
        }

        if(!SSN.isEmpty() && !DOB.isEmpty()){
            queryStringPart2 = " AND PatientSSN = '" + SSN + "'" + "AND PatientDOB = '" + DOB + "'";
        }

        if(SSN.isEmpty() && !DOB.isEmpty()){
            queryStringPart2 = " AND PatientDOB = '" + DOB + "'";
        }

        return queryStringPart2;

    }


    QString addPatient(QString patientName, QString patientLastName, QString patientDOB, QString &addPatientResult, QString patientMiddleName = "", QString patientSSN = "", QString patientEmail = "",QString patientMobile = "",QString patientWorkPhone = "",QString patientHomePhone = "", QString patientAdderssStreet = "",QString patientAddressLine2 = "",QString patientCity = "",QString patientState = "",QString patientZip = ""){

        QString addPatientQueryString;
        QString addPatientQueryStringSet;
        checkphone cp;
        CheckValid ck;
        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        if (patientName.isEmpty() && patientLastName.isEmpty() && patientDOB.isEmpty()){
            addPatientResult = "<p style=\"color:red\">Please enter basic information of the patient!</p>";
        }
        else if (patientName.isEmpty()){
            addPatientResult = "<p style=\"color:red\">Please enter the first name of the patient!</p>";
        }
        else if (patientLastName.isEmpty()){
            addPatientResult = "<p style=\"color:red\">Please enter the last name of the patient!</p>";
        }
        else if (patientDOB.isEmpty()){
            addPatientResult = "<p style=\"color:red\">Please enter the date of birth of the patient!</p>";
        }
        else if (patientMobile.isEmpty()){
            addPatientResult = "<p style=\"color:red\">Please enter the Mobile Phone number of the patient!</p>";
        }
        else if (!ck.is_valid(patientEmail)){
            addPatientResult = "<p style=\"color:red\">Please enter a valid email address for the patient!</p>";
        }
        else if (!cp.check(patientMobile)){
            addPatientResult = "<p style=\"color:red\">Please enter a valid phone number of the patient!</p>";
        }
        else{
            QSqlQuery query;
            addPatientQueryStringSet = queryAddPatientStringConstructor(patientName,patientLastName,patientDOB,patientMiddleName,patientSSN,patientEmail,patientMobile,patientWorkPhone,patientHomePhone,patientAdderssStreet,patientAddressLine2,patientCity,patientState,patientZip);
            qDebug() << "First and last name are provided";
            query.prepare(addPatientQueryStringSet);
            query.exec();
            qDebug() << "First and last name are provided";
            addPatientResult = "<p style=\"color:green\">Patient is added!</p>";
        }

    return addPatientResult;
    }

    QString addAppointment(QString patientID, QString doctorID, QString appointmentDate, QString appointmentReason, QString appointmentNotes, QString addAppointmentStatus,QString patientName,QString patientLastName,QString patientDOB){

        QString addAppointmentQueryString;
        QString addAppointmentResult;

        qDebug() << "In addPointment";

        databaseController dc;
        bool databaseConnected = dc.initDatabase();
        if (databaseConnected){

            qDebug() << "databse is connected";

            QSqlQuery query;
            QString queryAddPatientColumns = "INSERT INTO PatientsAppointments (PatientID, DoctorID, AppointmentDate, AppointmentReason, AppointmentNotes, AppointmentStatus, PatientName, PatientLastName, PatientDOB)";
            QString queryAddPatientValues = " VALUES ('" + patientID + "', '" + doctorID + "', '" + appointmentDate + "', '" + appointmentReason + "', '" + appointmentNotes + "', '"+addAppointmentStatus+"', '" + patientName + "', '" + patientLastName + "', '" + patientDOB + "')";
            addAppointmentQueryString = queryAddPatientColumns + queryAddPatientValues;
            qDebug() << addAppointmentQueryString;


            query.prepare(addAppointmentQueryString);
            query.exec();
            addAppointmentResult = "<p style=\"color:green\">Appointment is added!</p>";
        }

    return addAppointmentResult;
    }

    QString queryAddPatientStringConstructor(QString patientName, QString patientLastName, QString patientDOB, QString patientMiddleName = "", QString patientSSN = "", QString patientEmail = "",QString patientMobile = "",QString patientWorkPhone = "",QString patientHomePhone = "", QString patientAdderssStreet = "",QString patientAddressLine2 = "",QString patientCity = "",QString patientState = "",QString patientZip = ""){

        QString queryAddPatientColumns = "INSERT INTO Patients (PatientName, PatientLastName, PatientDOB";
        QString queryAddPatientValues = " VALUES ('" + patientName + "', '" + patientLastName + "', '" + patientDOB + "'";
        QString queryAddPatientString;

        if(!patientMiddleName.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientMiddleName";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientMiddleName + "'";
        }

        if(!patientSSN.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientSSN";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientSSN + "'";
        }

        if(!patientEmail.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientEmail";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientEmail + "'";
        }

        if(!patientMobile.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientMobilePhone";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientMobile + "'";
        }

        if(!patientWorkPhone.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientWorkPhone";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientWorkPhone + "'";
        }

        if(!patientHomePhone.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientHomePhone";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientHomePhone + "'";
        }

        if(!patientAdderssStreet.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientAdderssStreet";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientAdderssStreet + "'";
        }

        if(!patientAddressLine2.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientAddressLine2";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientAddressLine2 + "'";
        }

        if(!patientCity.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientAddressCity";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientCity + "'";
        }

        if(!patientState.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientAddressState";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientState + "'";
        }

        if(!patientZip.isEmpty()){
           queryAddPatientColumns = queryAddPatientColumns + ", PatientAddressZipCode";
           queryAddPatientValues = queryAddPatientValues + ", '" + patientZip + "'";
        }



        queryAddPatientColumns = queryAddPatientColumns + ")";
        queryAddPatientValues = queryAddPatientValues + ")";

        queryAddPatientString = queryAddPatientColumns + queryAddPatientValues;
        return queryAddPatientString;

    }


private:

    };



#endif // PATIENTSMODEL_H
