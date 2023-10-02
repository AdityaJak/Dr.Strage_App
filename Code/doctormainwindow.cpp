#include "doctormainwindow.h"
#include "ui_doctormainwindow.h"
#include <PatientsModel.h>
#include <QSqlDatabase>
#include <databaseController.h>
#include "qsqltablemodel.h"
#include "mainwindow.h"
#include "UserLoginModel.h"

DoctorMainWindow::DoctorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoctorMainWindow)
{
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(quit()));
    ui->setupUi(this);
    loadAppointments();
    ui->PatientQueryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->appointmentsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

DoctorMainWindow::~DoctorMainWindow()
{
    delete ui;
}

void DoctorMainWindow::on_SearchButton_clicked()
{

    QString firstName = ui->FirstNameLine->text();
    QString lastName = ui->LastNameLine->text();
    QString SSN = ui->SSNLine->text();
    QString DOB = ui->DOBLine->text();
    QString queryLabel = "";
    QString queryString;

    PatientsModel pm;
    ui->searchResultLabel->setText("");
    pm.queryPatient(firstName,lastName,queryLabel, queryString,SSN,DOB);
    ui->searchResultLabel->setText(queryLabel);

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    querymodel->setHeaderData(3, Qt::Horizontal, tr("DOB"));
    querymodel->setHeaderData(4, Qt::Horizontal, tr("Email"));
    querymodel->setHeaderData(5, Qt::Horizontal, tr("Phone Number"));
    ui->PatientQueryTable->setModel(querymodel);
    qDebug() << "Test";

}


void DoctorMainWindow::on_addPatientSaveButton_clicked()
{
    QString firstName = ui->addPatientName->text();
    QString lastName = ui->addPatientLastName->text();
    QString DOB = ui->addPatientDOB->text();
    QString addPatientResultLabel;

    QString patientMiddleName = ui->addPatientMiddleName->text();
    QString patientSSN = ui->addPatientSSN->text();
    QString patientEmail = ui->addPatientEmail->text();
    QString patientMobile = ui->addPatientMobile->text();
    QString patientWorkPhone = ui->addPatientWorkPhone->text();
    QString patientHomePhone = ui->addPatientHomePhone->text();
    QString patientAdderssStreet = ui->addPatientAddressLine1->text();
    QString patientAddressLine2 = ui->addPatientAddressLine2->text();
    QString patientCity = ui->addPatientCity->text();
    QString patientState = ui->addPatientState->text();
    QString patientZip = ui->addPatientZip->text();


    PatientsModel pm;
    pm.addPatient(firstName, lastName, DOB,addPatientResultLabel,patientMiddleName,patientSSN,patientEmail,patientMobile,patientWorkPhone,patientHomePhone,patientAdderssStreet,patientAddressLine2,patientCity,patientState,patientZip);

    ui->addPatientResultLabel->setText(addPatientResultLabel);
}


void DoctorMainWindow::on_PatientQueryTable_doubleClicked(const QModelIndex &index)
{
    patientupdate = new PatientUpdate(this);
    patientupdate->setModal(true);
    patientupdate->show();
    QStringList patientResults;

    QList varIndex = ui->PatientQueryTable->selectionModel()->selectedIndexes();
    QModelIndex varIndex2 =ui->PatientQueryTable->selectionModel()->currentIndex();
    QList varIndex4 =ui->PatientQueryTable->selectionModel()->selectedIndexes();
    QStringList patientData;
    QString doctorID = ui->DoctorWindouserNameLabel->text();



    for (int i = 0; i < varIndex.size(); i++){
            patientData.append(varIndex[i].data().toString());
    }

    PatientsModel pmNew;
    patientResults = pmNew.queryPatientForUpdate(patientData[0]);
    patientResults.append(doctorID);
    qDebug() << patientResults;
    connect(this, SIGNAL(sendData(QStringList)), patientupdate, SLOT(receiveData(QStringList)));
    emit sendData(patientResults);

}


void DoctorMainWindow::receiveData(QStringList loginUserData)
{
    QString logInUserID = loginUserData[0];
    UserLoginModel ulm;
    QStringList logInUserDataPassed = ulm.getLogInUserDoctors(logInUserID);
    ui->DoctorWindouserNameLabel->setText(logInUserDataPassed[0]);
    ui->userIDLabel->setText(logInUserID);
    ui->hospitalIDLabel->setText(logInUserDataPassed[1]);
    ui->drNameLabel->setText(logInUserDataPassed[5]);
    qDebug() << logInUserDataPassed;


}


void DoctorMainWindow::loadAppointments()
{

    QString doctorID = ui->DoctorWindouserNameLabel->text();
    QString patientSSN = ui->userIDLabel->text();
    QString patientEmail = ui->hospitalIDLabel->text();
    QString patientMobile = ui->drNameLabel->text();

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    QString queryString = "SELECT AppointmentDate, PatientID, PatientName, PatientLastName, PatientDOB, AppointmentReason, AppointmentNotes   FROM PatientsAppointments WHERE DoctorID = " + doctorID;

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("AppointmentDate"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("PatientID"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("PatientName"));
    querymodel->setHeaderData(3, Qt::Horizontal, tr("Patient Last Name"));
    querymodel->setHeaderData(4, Qt::Horizontal, tr("DOB"));
    querymodel->setHeaderData(5, Qt::Horizontal, tr("Appointment Reason"));
    querymodel->setHeaderData(5, Qt::Horizontal, tr("Appointment Notes"));
    ui->appointmentsTableView->setModel(querymodel);
    qDebug() << "Test";


}



void DoctorMainWindow::on_logoutButton_clicked()
{
    MainWindow* the_main = new MainWindow();
    the_main->show();
    hide();
}


void DoctorMainWindow::on_pushButton_clicked()
{
    QString doctorID = ui->DoctorWindouserNameLabel->text();
    QString patientSSN = ui->userIDLabel->text();
    QString patientEmail = ui->hospitalIDLabel->text();
    QString patientMobile = ui->drNameLabel->text();

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    QString queryString = "SELECT AppointmentDate, PatientID, PatientName, PatientLastName, PatientDOB, AppointmentReason, AppointmentNotes   FROM PatientsAppointments WHERE DoctorID = " + doctorID;

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("AppointmentDate"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("PatientID"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("PatientName"));
    querymodel->setHeaderData(3, Qt::Horizontal, tr("Patient Last Name"));
    querymodel->setHeaderData(4, Qt::Horizontal, tr("DOB"));
    querymodel->setHeaderData(5, Qt::Horizontal, tr("Appointment Reason"));
    querymodel->setHeaderData(5, Qt::Horizontal, tr("Appointment Notes"));
    ui->appointmentsTableView->setModel(querymodel);
    qDebug() << "Test";
}


void DoctorMainWindow::on_appointmentsTableView_doubleClicked(const QModelIndex &index)
{
    patientupdate = new PatientUpdate(this);
    patientupdate->setModal(true);
    patientupdate->show();
    QStringList patientResults;
    QString doctorID = ui->DoctorWindouserNameLabel->text();

    QList varIndex = ui->appointmentsTableView->selectionModel()->selectedIndexes();
    QModelIndex varIndex2 =ui->appointmentsTableView->selectionModel()->currentIndex();
    QList varIndex4 =ui->appointmentsTableView->selectionModel()->selectedIndexes();
    QStringList patientData;



    for (int i = 0; i < varIndex.size(); i++){
            patientData.append(varIndex[i].data().toString());
    }

    PatientsModel pmNew;
    patientResults = pmNew.queryPatientForUpdate(patientData[0]);
    patientResults.append(doctorID);
    qDebug() << patientResults;
    connect(this, SIGNAL(sendData(QStringList)), patientupdate, SLOT(receiveData(QStringList)));
    emit sendData(patientResults);
}

