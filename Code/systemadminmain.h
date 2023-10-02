#ifndef SYSTEMADMINMAIN_H
#define SYSTEMADMINMAIN_H

#include <QMainWindow>
#include "qsqltablemodel.h"

namespace Ui {
class systemAdminMain;
}

class systemAdminMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit systemAdminMain(QWidget *parent = nullptr);
    ~systemAdminMain();

private slots:
    void on_viewHospitalsLoadButton_clicked();
    void on_addHospitalButton_clicked();
    void receiveData(QStringList);
    void on_viewHospitalsSearchButton_clicked();
    void on_addHospitalAdminSearchButton_clicked();
    void on_SearchButton_clicked();
    void on_logoutButton_clicked();

    void on_addPatientSaveButton_clicked();

    void on_addHospitalAdminAddButton_clicked();

private:
    Ui::systemAdminMain *ui;
    QSqlTableModel *sqlTableModel;
    QSqlQueryModel *querymodel;
};

#endif // SYSTEMADMINMAIN_H
