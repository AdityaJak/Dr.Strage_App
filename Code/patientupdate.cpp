#include "patientupdate.h"
#include "ui_patientupdate.h"
#include <PatientsModel.h>
#include "appointments.h"

PatientUpdate::PatientUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientUpdate)
{
    ui->setupUi(this);
}

PatientUpdate::~PatientUpdate()
{
    delete ui;
}

void PatientUpdate::receiveData(QStringList patientDataSent){
    ui->patientUpdatePatientID->setText(patientDataSent[0]);
    ui->patientUpdateFirstNameText->setText(patientDataSent[1]);
    ui->patientUpdateMiddleNameText->setText(patientDataSent[2]);
    ui->patientUpdateLastNameText->setText(patientDataSent[3]);
    ui->patientUpdateDOB->setText(patientDataSent[4]);
    ui->patientUpdateSSN->setText(patientDataSent[5]);
    ui->patientUpdateEmail->setText(patientDataSent[6]);
    ui->patientUpdateMobile->setText(patientDataSent[7]);
    ui->patientUpdateWorkPhone->setText(patientDataSent[8]);
    ui->patientUpdateHomePhone->setText(patientDataSent[9]);
    ui->patientUpdateAddressLine1->setText(patientDataSent[10]);
    ui->patientUpdateAddressLine2->setText(patientDataSent[11]);
    ui->patientUpdateCity->setText(patientDataSent[12]);
    ui->patientUpdateState->setText(patientDataSent[13]);
    ui->patientUpdateZip->setText(patientDataSent[14]);
    ui->patientUpdateDoctorIDLabel->setText(patientDataSent[15]);

}

void PatientUpdate::on_updatePatientUpdateButton_clicked()
{
    QString patientID = ui->patientUpdatePatientID->text();
    QString patientfirstName = ui->patientUpdateFirstNameText->text();
    QString patientmiddleName = ui->patientUpdateMiddleNameText->text();
    QString patientLastName = ui->patientUpdateLastNameText->text();
    QString patientDOB = ui->patientUpdateDOB->text();
    QString patientSSN = ui->patientUpdateSSN->text();
    QString patientEmail = ui->patientUpdateEmail->text();
    QString patientMobile = ui->patientUpdateMobile->text();
    QString patientWorkPhone = ui->patientUpdateWorkPhone->text();
    QString patientHomePhone = ui->patientUpdateHomePhone->text();
    QString patientAddress1 = ui->patientUpdateAddressLine1->text();
    QString patientAddress2 = ui->patientUpdateAddressLine2->text();
    QString patientcity = ui->patientUpdateCity->text();
    QString patientstate = ui->patientUpdateState->text();
    QString patientzip = ui->patientUpdateZip->text();

    PatientsModel pm;
    QString updatePatientResultLabel = "";
    pm.updatePatient(patientID, patientfirstName, patientmiddleName,patientLastName,patientDOB,patientSSN,patientEmail,patientMobile,patientWorkPhone,patientHomePhone,patientAddress1,patientAddress2,patientcity,patientstate,patientzip,updatePatientResultLabel);

    ui->updatePatientStatusLabel->setText(updatePatientResultLabel);
}


void PatientUpdate::on_pushButton_clicked()
{
    QString patientID = ui->patientUpdatePatientID->text();
    QString patientfirstName = ui->patientUpdateFirstNameText->text();
    QString patientLastName = ui->patientUpdateLastNameText->text();
    QString patientDOB = ui->patientUpdateDOB->text();
    QString patientDoctorID = ui->patientUpdateDoctorIDLabel->text();
    appointment = new Appointments(this);
    appointment->setModal(true);
    appointment->show();
    QStringList patientData;
    patientData.append(patientID);
    patientData.append(patientDoctorID);
    patientData.append(patientfirstName);
    patientData.append(patientLastName);
    patientData.append(patientDOB);

    connect(this, SIGNAL(sendData(QStringList)), appointment, SLOT(receiveData(QStringList)));
    emit sendData(patientData);
}

