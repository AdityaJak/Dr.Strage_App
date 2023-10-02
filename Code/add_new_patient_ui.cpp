#include "add_new_patient_ui.h"
#include "ui_add_new_patient_ui.h"
#include <PatientsModel.h>
#include "doctor_main.h"
#include <QMessageBox>

add_new_patient_ui::add_new_patient_ui(QWidget *parent, MainWindow *mainwindow, doctor_main *doctormianui) :
    QDialog(parent),
    main_window(mainwindow),
    doctor_main_ui(doctormianui),
    ui(new Ui::add_new_patient_ui)
{
    ui->setupUi(this);
}

add_new_patient_ui::~add_new_patient_ui()
{
    delete ui;
}



// when close window
void add_new_patient_ui::on_add_new_patient_ui_rejected()
{
    main_window->show();
    main_window->close();
}

// Back button
// Back to doctor main ui
void add_new_patient_ui::on_pushButton_clicked()
{
    doctor_main_ui->show();
    this->hide();
}

// Add button
// Add patient data to database
void add_new_patient_ui::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Confirm", "Patient Data Uploaded Successfully");
}


void add_new_patient_ui::on_addPatientSave_clicked()
{
    QString firstName = ui->addPatientFirstName->text();
    QString lastName = ui->addPatientLastName->text();
    QString DOB = ui->addPatientDOB->text();
    QString addPatientResultLabel;

    QString patientMiddleName = ui->addPatientMiddleName->text();
    QString patientSSN = ui->addPatientSSN->text();
    QString patientEmail = ui->addPatientEmail->text();
    QString patientMobile = ui->addPatientMobilePhone->text();
    QString patientWorkPhone = ui->addPatientWorkPhone->text();
    QString patientHomePhone = ui->addPatientHomePhone->text();
    QString patientAdderssStreet = ui->addPatientAddress1->text();
    QString patientAddressLine2 = ui->addPatientAddress2->text();
    QString patientCity = ui->addPatientAddressCity->text();
    QString patientState = ui->addPatientAddressState->text();
    QString patientZip = ui->addPatientAddressZip->text();


    PatientsModel pm;
    pm.addPatient(firstName, lastName, DOB,addPatientResultLabel,patientMiddleName,patientSSN,patientEmail,patientMobile,patientWorkPhone,patientHomePhone,patientAdderssStreet,patientAddressLine2,patientCity,patientState,patientZip);

    ui->addPatientResult->setText(addPatientResultLabel);

}

