#include "appointments.h"
#include "ui_appointments.h"
#include <PatientsModel.h>

Appointments::Appointments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Appointments)
{
    ui->setupUi(this);
}

Appointments::~Appointments()
{
    delete ui;
}


void Appointments::receiveData(QStringList patientDataSent){
    ui->appointmentsPatientIDLabel->setText(patientDataSent[0]);
    ui->appointmentsDoctorIDLabel->setText(patientDataSent[1]);
    ui->appointmentsPatientNameLabel->setText(patientDataSent[2]);
    ui->appointmentsPatientLastNameLabel->setText(patientDataSent[3]);
    ui->appointmentsPatientDOB->setText(patientDataSent[4]);

}

void Appointments::on_createAppointmentButton_clicked()
{
   QString patietnID = ui->appointmentsPatientIDLabel->text();
    QString doctorID =ui->appointmentsDoctorIDLabel->text();
   QString patietnName = ui->appointmentsPatientNameLabel->text();
    QString patietnLastName =ui->appointmentsPatientLastNameLabel->text();
   QString patietnAppointmentReason = ui->appointmentReasonText->toPlainText();
   QString patietnAppointmentNotes = ui->appointmentNoesText->toPlainText();
   QString patietnAppointmentTime = ui->appointmentDateTimeEdit->text();
   QString patietnDOB = ui->appointmentsPatientDOB->text();
   QString pattientAppointmentStatus = "1";

   qDebug() << patietnAppointmentTime;

   QString addAppointmentResults;

   PatientsModel pm;
   QString createAppointmentResultLabel = "";
   addAppointmentResults = pm.addAppointment(patietnID, doctorID, patietnAppointmentTime,patietnAppointmentReason,patietnAppointmentNotes,pattientAppointmentStatus,patietnName,patietnLastName,patietnDOB);

   ui->createAppointmentStatusLabel->setText(addAppointmentResults);

}

