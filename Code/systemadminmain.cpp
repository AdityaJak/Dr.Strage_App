#include "systemadminmain.h"
#include "ui_systemadminmain.h"
#include <QSqlDatabase>
#include <databaseController.h>
#include "qsqltablemodel.h"
#include "UserSystemAdminModel.h"
#include "mainwindow.h"
#include <PatientsModel.h>

systemAdminMain::systemAdminMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::systemAdminMain)
{
    ui->setupUi(this);
    ui->HospitalQueryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->PatientQueryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

systemAdminMain::~systemAdminMain()
{
    delete ui;
}

void systemAdminMain::receiveData(QStringList loginUserData)
{
    QString logInUserID = loginUserData[0];
    ui->label->setText(logInUserID);


}

void systemAdminMain::on_viewHospitalsLoadButton_clicked()
{
    // your code placed here
    QString queryString = "SELECT * FROM drstrangev0.Hospitals";

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("Hospital ID"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("Hospital Name"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("Address Line 1"));
    querymodel->setHeaderData(3, Qt::Horizontal, tr("Address Line 2"));
    querymodel->setHeaderData(4, Qt::Horizontal, tr("City"));
    querymodel->setHeaderData(5, Qt::Horizontal, tr("State"));
    querymodel->setHeaderData(6, Qt::Horizontal, tr("Zip Code"));
    querymodel->setHeaderData(7, Qt::Horizontal, tr("Country"));
    ui->HospitalQueryTable->setModel(querymodel);
    qDebug() << "Test";
}

void systemAdminMain::on_addHospitalButton_clicked()
{
    QString HospitalName = ui->addHospitalName->text();
        QString HospitalAdd1 = ui->addHospitalAddressLine1->text();
        QString HospitalAdd2 = ui->addHospitalAddressLine2->text();
        QString HospitalCity = ui->addHospitalCity->text();
        QString HospitalState = ui->addHospitalState->text();
        QString HospitalZip = ui->addHospitalZip->text();
        QString HospitalCountry = ui->addHospitalCountry->text();
        QString addHospitalStatusLabel;

        UserSystemAdminModel us;
        addHospitalStatusLabel = us.addHospital(HospitalName, HospitalAdd1, HospitalAdd2, HospitalCity, HospitalState, HospitalZip, HospitalCountry);
         QString newHospitalID = us.getNewHospitalID();
         addHospitalStatusLabel = addHospitalStatusLabel + "New hospital ID is " + newHospitalID + ".";
        ui->addHospitalStatusLabel->setText(addHospitalStatusLabel);
}

void systemAdminMain::on_viewHospitalsSearchButton_clicked()
{
    QString HospitalName = ui->viewHospitalNameSearchField->text();
    QString HospitalID = ui->viewHospitalIDSearchField->text();

    UserSystemAdminModel us;
    QString queryResult = "";
    QString queryString = "";
    us.queryUserAdmin(HospitalName,HospitalID,queryResult,queryString);
    ui->HospitalSearchLabel->setText(queryResult);

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    if(databaseConnected){
        querymodel = new QSqlQueryModel();
        querymodel->setQuery(queryString);
        querymodel->setHeaderData(0, Qt::Horizontal, tr("Hospital ID"));
        querymodel->setHeaderData(1, Qt::Horizontal, tr("Hospital Name"));
        querymodel->setHeaderData(2, Qt::Horizontal, tr("Address Line 1"));
        querymodel->setHeaderData(3, Qt::Horizontal, tr("Address Line 2"));
        querymodel->setHeaderData(4, Qt::Horizontal, tr("City"));
        querymodel->setHeaderData(5, Qt::Horizontal, tr("State"));
        querymodel->setHeaderData(6, Qt::Horizontal, tr("Zip Code"));
        querymodel->setHeaderData(7, Qt::Horizontal, tr("Country"));
        ui->HospitalQueryTable->setModel(querymodel);
        qDebug()<< "Test connection";
    }
}



void systemAdminMain::on_addHospitalAdminSearchButton_clicked()
{
    QString HospitalName = ui->viewHospitalNameSearchField_2->text();
    QString HospitalID = ui->viewHospitalIDSearchField_2->text();

    UserSystemAdminModel us;
    QString queryResult = "";
    QString queryString = "";
    us.queryUserAdmin(HospitalName,HospitalID,queryResult,queryString);
    if(queryResult.isEmpty()){
        queryResult = "<p style=\"color:white\">Hospital found!</p>";
    }
    ui -> addHospitalAdminSearchResult->setText(queryResult);
}


void systemAdminMain::on_SearchButton_clicked()
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
    querymodel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("Last Name"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("DOB"));
    ui->PatientQueryTable->setModel(querymodel);
    qDebug() << "Test";
}


void systemAdminMain::on_logoutButton_clicked()
{
    MainWindow* the_main = new MainWindow();
    the_main->show();
    hide();
}


void systemAdminMain::on_addPatientSaveButton_clicked()
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


void systemAdminMain::on_addHospitalAdminAddButton_clicked()
{
    QString FirstName = ui->addHospitalAdminFirstName->text();
    QString MiddleName = ui->addHospitalAdminMiddleName->text();
    QString LastName = ui->addHospitalAdminLastName->text();
    QString UserId = ui->addHospitalAdminUserID->text();
    QString EmailId = ui->addHospitalAdminEmail->text();
    QString OfficePhone = ui->addHospitalAdminOfficePhone->text();
    QString MobilePhone = ui->addHospitalAdminMobilePhone->text();
    QString HospitalID = ui->viewHospitalIDSearchField_2->text();
    QString password = ui->addHospitalAdminTempPassword->text();

    if(HospitalID.isEmpty()){
        QString HospitalName = ui->viewHospitalNameSearchField_2->text();
        UserSystemAdminModel us;
        QString queryResult = "";
        QString queryString = "";
        us.queryUserAdmin(HospitalName,HospitalID,queryResult,queryString);
    }

    QString addHospitalAdminStatus = "";
    UserSystemAdminModel us;
    addHospitalAdminStatus = us.addHospitalAdmin(FirstName, MiddleName, LastName, UserId, EmailId, OfficePhone, MobilePhone, HospitalID,password);
    ui->addHospitalAdminAddResult->setText(addHospitalAdminStatus);
}

