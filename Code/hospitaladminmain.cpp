#include "hospitaladminmain.h"
#include "ui_hospitaladminmain.h"
#include "mainwindow.h"
#include "UserLoginModel.h"
#include "HospitalAdminModel.h"
#include "UserSystemAdminModel.h"
#include "DoctorModel.h"
#include <PatientsModel.h>
#include "qsqltablemodel.h"

hospitalAdminMain::hospitalAdminMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hospitalAdminMain)
{
    ui->setupUi(this);
    ui->HospitalQueryTable_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->HospitalQueryTable_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->PatientQueryTable_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

hospitalAdminMain::~hospitalAdminMain()
{
    delete ui;
}

void hospitalAdminMain::receiveData(QStringList loginUserData)
{
    QString logInUserID = loginUserData[0];
    UserLoginModel ulm;
    QStringList logInUserDataPassed = ulm.getLogInUserHospitalAdmin(logInUserID);
    ui->hospitalAdminUserNameLabel->setText(logInUserID);
    ui->hospitalAdminHospitalID->setText(logInUserDataPassed[0]);

    ui->addAdminsMyHospitalNameLabel->setText(logInUserDataPassed[1]);
    ui->addAdminsMyHospitalIDLabel->setText(logInUserDataPassed[0]);
    ui->addDoctorMyHospitalNameLabel->setText(logInUserDataPassed[1]);
    ui->addDoctorMyHospitalIDLabel->setText(logInUserDataPassed[0]);


    qDebug() << logInUserDataPassed;


}



void hospitalAdminMain::on_logoutButton_clicked()
{
    MainWindow* the_main = new MainWindow();
    the_main->show();
    hide();
}


void hospitalAdminMain::on_viewAdminsLoadAllButton_clicked()
{
    //where to find the database
    QString HospitalID = ui->hospitalAdminHospitalID->text();
    QString queryString = "SELECT * FROM drstrangev0.UserHospitalAdmins WHERE HospitalID = '" + HospitalID + "'";

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("ID"));

    ui->HospitalQueryTable_2->setModel(querymodel);

}


void hospitalAdminMain::on_viewAdminsSearchButton_clicked()
{
    QString firstName = ui->viewAdminsNameSearchField ->text();
    QString lastName = ui->viewAdminsLastNameSearchField->text();
    QString ID = ui->viewAdminsUserIdSearchField->text();
    QString Email = ui->viewAdminsEmailSearchField->text();
    QString queryLabel = "";
    QString queryString;

    hospitalAdminModel pm;

    pm.queryHospitalAdmin(firstName,lastName,queryLabel, queryString,ID,Email);

    databaseController dc;
    bool databaseConnected = dc.initDatabase();
    qDebug() << "check querymodel";
    qDebug() << queryString;
    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("Middle Name"));
    querymodel->setHeaderData(3, Qt::Horizontal, tr("Last Name"));
    ui->HospitalQueryTable_2->setModel(querymodel);
    qDebug() << "Test";
}


void hospitalAdminMain::on_addHospitalAdminAddButton_2_clicked()
{
    QString FirstName = ui->addHospitalAdminFirstName_2->text();
        QString MiddleName = ui->addHospitalAdminMiddleName_2->text();
        QString LastName = ui->addHospitalAdminLastName_2->text();
        QString EmailId = ui->addHospitalAdminEmail_2->text();
        QString MobilePhone = ui->addHospitalAdminMobilePhone_2->text();
        QString OfficePhone = ui->addHospitalAdminOfficePhone_2->text();
        QString UserId = ui->addHospitalAdminUserID_2->text();
         QString HospitalID = ui->hospitalAdminHospitalID->text();
        QString password = ui->addHospitalAdminTempPassword_2->text();

            QString addHospitalAdminStatus = "";
            UserSystemAdminModel us;
            addHospitalAdminStatus = us.addHospitalAdmin(FirstName, MiddleName, LastName, UserId, EmailId, OfficePhone, MobilePhone, HospitalID,password);
            ui->addHospitalAdminAddResult_2->setText(addHospitalAdminStatus);
}


void hospitalAdminMain::on_viewDoctorsLoadAllButton_clicked()
{
     QString HospitalID = ui->hospitalAdminHospitalID->text();
    //where to find the database
    QString queryString = "SELECT ID, HospitalID, ProviderID, NameParts_Given, NameParts_Family, AddressCity FROM drstrangev0.UserDoctors WHERE HospitalID = '" + HospitalID + "'";

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("ID"));

    ui->HospitalQueryTable_3->setModel(querymodel);

}


void hospitalAdminMain::on_addHospitalAdminAddButton_3_clicked()
{
    QString Hname =ui->addDoctorMyHospitalNameLabel ->text();
    QString Hid =ui->addDoctorMyHospitalIDLabel->text();
    QString fn = ui->addDoctorFirstName->text();
    QString mn = ui->addDoctorMiddleName->text();
    QString ln = ui->addDoctorLastName->text();

    QString Email = ui->addDoctorEmail->text();
    QString Mphone = ui->addDoctorMobile->text();
    QString Ophone = ui->addDoctorOfficePhone->text();

    QString PID = ui->addDoctorProviderID->text();
    QString A1 = ui->addDoctorAddress1->text();
    QString A2 = ui->addDoctorAddress2->text();

    QString City = ui->addDoctorCity->text();
    QString state = ui->addDoctorState->text();
    QString ling = ui->addDoctorLanguage->text();
    QString zip = ui->addDoctorZIP->text();

    QString UID = ui->addHospitalAdminUserID_3->text();
    QString password = ui->addHospitalAdminTempPassword_3->text();

    QString addDoctorResult = "";
    QString addHospitalStatusLabel;

    DoctorModel us;

    us.addDoctor(addDoctorResult, Hid, ling, UID, ln, fn, zip, state, City, A1, Email, Mphone);
    us.addUserLogin(Email, UID, password);
      ui->addDoctorStatusLabel2->setText("<p style=\"color:green\">Doctor is sucessfully added!</p>");
}


void hospitalAdminMain::on_viewDoctorsSearchButton_clicked()
{
    QString firstName = ui->viewDoctorsNameSearchField->text();
    QString lastName = ui->viewDoctorsLastNameSearchField->text();
    QString DoctorID = ui->viewDoctorsUserIdSearchField->text();
    QString email = ui->viewDoctorsEmailSearchField->text();
    QString hospitalID = ui->hospitalAdminHospitalID->text();

    DoctorModel dm;
    QString resultLabel = "";
    QString queryString = "";
    dm.queryDoctor(firstName,lastName,resultLabel,queryString,DoctorID,email);

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("ID"));

    ui->HospitalQueryTable_3->setModel(querymodel);

}


void hospitalAdminMain::on_SearchButton_2_clicked()
{
    QString firstName = ui->FirstNameLine_2->text();
    QString lastName = ui->LastNameLine_2->text();
    QString SSN = ui->SSNLine_2->text();
    QString DOB = ui->DOBLine_2->text();
    QString queryLabel = "";
    QString queryString;

    PatientsModel pm;
    ui->searchResultLabelHospitalAdmin->setText("");
    pm.queryPatient(firstName,lastName,queryLabel, queryString,SSN,DOB);
    ui->searchResultLabelHospitalAdmin->setText(queryLabel);

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("Last Name"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("DOB"));
    ui->PatientQueryTable_2->setModel(querymodel);
    qDebug() << "Test";
}


void hospitalAdminMain::on_addPatientSaveButton_2_clicked()
{
    QString firstName = ui->addPatientName_2->text();
    QString lastName = ui->addPatientLastName_2->text();
    QString DOB = ui->addPatientDOB_2->text();
    QString addPatientResultLabel;

    QString patientMiddleName = ui->addPatientMiddleName_2->text();
    QString patientSSN = ui->addPatientSSN_2->text();
    QString patientEmail = ui->addPatientEmail_2->text();
    QString patientMobile = ui->addPatientMobile_2->text();
    QString patientWorkPhone = ui->addPatientWorkPhone_2->text();
    QString patientHomePhone = ui->addPatientHomePhone_2->text();
    QString patientAdderssStreet = ui->addPatientAddressLine1_2->text();
    QString patientAddressLine2 = ui->addPatientAddressLine2_2->text();
    QString patientCity = ui->addPatientCity_2->text();
    QString patientState = ui->addPatientState_2->text();
    QString patientZip = ui->addPatientZip_2->text();


    PatientsModel pm;
    pm.addPatient(firstName, lastName, DOB,addPatientResultLabel,patientMiddleName,patientSSN,patientEmail,patientMobile,patientWorkPhone,patientHomePhone,patientAdderssStreet,patientAddressLine2,patientCity,patientState,patientZip);

    ui->addResultsLabelHospitalAdmin->setText(addPatientResultLabel);

}

