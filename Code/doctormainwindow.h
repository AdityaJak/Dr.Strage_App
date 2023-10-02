#ifndef DOCTORMAINWINDOW_H
#define DOCTORMAINWINDOW_H

#include <QMainWindow>
#include "qsqltablemodel.h"
#include "patientupdate.h"

namespace Ui {
class DoctorMainWindow;
}

class DoctorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorMainWindow(QWidget *parent = nullptr);
    ~DoctorMainWindow();

private slots:
    void receiveData(QStringList);
    void loadAppointments();
    void on_SearchButton_clicked();
    void on_addPatientSaveButton_clicked();
    void on_PatientQueryTable_doubleClicked(const QModelIndex &index);
    void on_logoutButton_clicked();
    void on_pushButton_clicked();
    void on_appointmentsTableView_doubleClicked(const QModelIndex &index);

signals:
    void sendData(QStringList);

private:
    Ui::DoctorMainWindow *ui;
    QSqlTableModel *sqlTableModel;
    QSqlQueryModel *querymodel;
    PatientUpdate *patientupdate;
};

#endif // DOCTORMAINWINDOW_H
