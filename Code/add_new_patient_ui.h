#ifndef ADD_NEW_PATIENT_UI_H
#define ADD_NEW_PATIENT_UI_H

#include <QDialog>
#include "mainwindow.h"

class doctor_main;

namespace Ui {
class add_new_patient_ui;
}

class add_new_patient_ui : public QDialog
{
    Q_OBJECT

public:
    explicit add_new_patient_ui(QWidget *parent = nullptr, MainWindow *mainwindow = nullptr, doctor_main *doctormianui = nullptr);
    ~add_new_patient_ui();

private slots:

    void on_add_new_patient_ui_rejected();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_addPatientSave_clicked();

private:
    Ui::add_new_patient_ui *ui;
    MainWindow * main_window;
    doctor_main *doctor_main_ui;
};

#endif // ADD_NEW_PATIENT_UI_H
