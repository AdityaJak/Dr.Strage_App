#ifndef SEARCH_PATIENT_SPECIFICLY_UI_H
#define SEARCH_PATIENT_SPECIFICLY_UI_H

#include <QDialog>
#include "mainwindow.h"
#include "qsqltablemodel.h"

namespace Ui {
class search_patient_specificly_ui;
}

class search_patient_specificly_ui : public QDialog
{
    Q_OBJECT

public:
    explicit search_patient_specificly_ui(QWidget *parent = nullptr, MainWindow *mainwindow = nullptr, doctor_main *doctormianui = nullptr);
    ~search_patient_specificly_ui();

private slots:
    void on_search_patient_specificly_ui_rejected();

    void on_pushButton_back_clicked();

    void on_patientSearchButton_clicked();

private:
    Ui::search_patient_specificly_ui *ui;
    doctor_main *doctor_main_ui;
    MainWindow * main_window;
    QSqlTableModel *sqlTableModel;
    QSqlQueryModel *querymodel;

};

#endif // SEARCH_PATIENT_SPECIFICLY_UI_H
