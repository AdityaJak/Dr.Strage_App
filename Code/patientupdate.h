#ifndef PATIENTUPDATE_H
#define PATIENTUPDATE_H

#include <QDialog>
#include "appointments.h"

namespace Ui {
class PatientUpdate;
}

class PatientUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit PatientUpdate(QWidget *parent = nullptr);
    ~PatientUpdate();

private slots:
    void receiveData(QStringList);
    void on_updatePatientUpdateButton_clicked();

    void on_pushButton_clicked();

signals:
    void sendData(QStringList);

private:
    Ui::PatientUpdate *ui;
    Appointments *appointment;
};



#endif // PATIENTUPDATE_H
