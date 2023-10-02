#include "search_patient_specificly_ui.h"
#include "ui_search_patient_specificly_ui.h"
#include <UserLoginModel.h>
#include "doctor_main.h"
#include "mainwindow.h"
#include <PatientsModel.h>
#include <QSqlDatabase>
#include <databaseController.h>
#include "./ui_mainwindow.h"


search_patient_specificly_ui::search_patient_specificly_ui(QWidget *parent, MainWindow *mainwindow, doctor_main *doctormainui) :
    QDialog(parent),
    main_window(mainwindow),
    doctor_main_ui(doctormainui),
    ui(new Ui::search_patient_specificly_ui)
{
    ui->setupUi(this);

}

search_patient_specificly_ui::~search_patient_specificly_ui()
{
    delete ui;
}

//Close button clicked
void search_patient_specificly_ui::on_search_patient_specificly_ui_rejected()
{
    main_window->show();
    main_window->close();
}


void search_patient_specificly_ui::on_pushButton_back_clicked()
{
    doctor_main_ui->show();
    this->hide();
}


void search_patient_specificly_ui::on_patientSearchButton_clicked()
{

    QString firstName = ui->searchFirstName->text();
    QString lastName = ui->searchLastName->text();
    QString SSN = ui->searchSSN->text();
    QString DOB = ui->searchDOB->text();
    QString queryLabel = "";
    QString queryString;

    PatientsModel pm;
    ui->searchResultsLabel->setText("");
    pm.queryPatient(firstName,lastName,queryLabel, queryString,SSN,DOB);
    ui->searchResultsLabel->setText(queryLabel);

    databaseController dc;
    bool databaseConnected = dc.initDatabase();

    querymodel = new QSqlQueryModel();
    querymodel->setQuery(queryString);
    querymodel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("Last Name"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("DOB"));
    ui->PatientsQueryTable->setModel(querymodel);
    qDebug() << "Test";



}

