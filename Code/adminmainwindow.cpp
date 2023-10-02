#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include "DoctorsModel.h"
#include <databaseController.h>
#include <QSqlDatabase>
#include "databaseController.h"

AdminMainWindow::AdminMainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::on_addDoctorSaveButton_clicked()
{
    QString Hospital = ui->hospitalID->text();
    //QString LanguageCommunite = ui->language->text();
    QString HospitalName = ui->hospitalname->text();
    QString UserID = ui->userid->text();
    QString language = ui->language->text();
    QString country = ui->addresscountry->text();
    QString familyname = ui->familyname->text();
    QString givenname = ui->givenname->text();
    //QString AddressCountry = ui->addresscountry->text();
    //QString AddressZipCode = ui->addresszipcode->text();
    //QString AddressState = ui->addressstate->text();
    //QString AddressCity = ui->addresscity->text();
    QString queryLabel = "";
    QString queryString;

    DoctorsModel pm;
    ui->searchResultLabel->setText("");
    pm.queryDoctor(HospitalName, country,queryLabel, queryString, familyname, givenname);
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
