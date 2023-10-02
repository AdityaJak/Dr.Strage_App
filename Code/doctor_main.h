#ifndef DOCTOR_MAIN_H
#define DOCTOR_MAIN_H

#include <QDialog>
#include "add_new_patient_ui.h"
#include "search_patient_specificly_ui.h"
#include "mainwindow.h"


namespace Ui {
class doctor_main;
}

class doctor_main : public QDialog
{
    Q_OBJECT

public:
    explicit doctor_main(QWidget *parent = nullptr, MainWindow *mainwindow = nullptr);
    ~doctor_main();

private slots:
    void on_pushButton_clicked();

    void on_doctor_main_rejected();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::doctor_main *ui;
    MainWindow * main_window;
    add_new_patient_ui *add_new_patient_ui_instance = nullptr;
    search_patient_specificly_ui *search_patient_specificly_ui_instance = nullptr;
};

#endif // DOCTOR_MAIN_H
