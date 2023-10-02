#include "doctor_main.h"
#include "ui_doctor_main.h"

doctor_main::doctor_main(QWidget *parent, MainWindow *mainwindow) :
    QDialog(parent),
    main_window(mainwindow),
    ui(new Ui::doctor_main)
{
    ui->setupUi(this);
}

doctor_main::~doctor_main()
{
    delete ui;
}

// open add_new_patient_ui
void doctor_main::on_pushButton_clicked()
{
    hide();
    if(!add_new_patient_ui_instance)
    {
        add_new_patient_ui_instance = new add_new_patient_ui(this, main_window, this);
    }else
    {
        delete add_new_patient_ui_instance;
        add_new_patient_ui_instance = new add_new_patient_ui(this, main_window, this);
    }

    add_new_patient_ui_instance->show();
}

// Search patient specificly button
void doctor_main::on_pushButton_2_clicked()
{
    hide();
    if(!search_patient_specificly_ui_instance)
    {
        search_patient_specificly_ui_instance = new search_patient_specificly_ui(this, main_window, this);
    }else
    {
        delete search_patient_specificly_ui_instance;
        search_patient_specificly_ui_instance = new search_patient_specificly_ui(this, main_window, this);
    }
    search_patient_specificly_ui_instance->show();
}


// when close window
void doctor_main::on_doctor_main_rejected()
{
    main_window->show();
    main_window->close();
}


// Log out button
void doctor_main::on_pushButton_4_clicked()
{
    main_window->show();
    hide();
}


