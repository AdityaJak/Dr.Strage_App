#ifndef HOSPITALADMINMAIN_H
#define HOSPITALADMINMAIN_H

#include <QMainWindow>
#include "qsqltablemodel.h"

namespace Ui {
class hospitalAdminMain;
}

class hospitalAdminMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit hospitalAdminMain(QWidget *parent = nullptr);
    ~hospitalAdminMain();

private slots:
    void receiveData(QStringList);
    void on_logoutButton_clicked();

    void on_viewAdminsLoadAllButton_clicked();

    void on_viewAdminsSearchButton_clicked();

    void on_addHospitalAdminAddButton_2_clicked();

    void on_viewDoctorsLoadAllButton_clicked();

    void on_addHospitalAdminAddButton_3_clicked();

    void on_viewDoctorsSearchButton_clicked();

    void on_SearchButton_2_clicked();

    void on_addPatientSaveButton_2_clicked();

private:
    Ui::hospitalAdminMain *ui;
    QSqlTableModel *sqlTableModel;
    QSqlQueryModel *querymodel;
};

#endif // HOSPITALADMINMAIN_H
