#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <QDialog>


namespace Ui {
class Appointments;
}

class Appointments : public QDialog
{
    Q_OBJECT

public:
    explicit Appointments(QWidget *parent = nullptr);
    ~Appointments();

private slots:
    void receiveData(QStringList);

    void on_createAppointmentButton_clicked();

private:
    Ui::Appointments *ui;
};

#endif // APPOINTMENTS_H
