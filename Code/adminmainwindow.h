#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include "qsqltablemodel.h"
#include "ui_adminmainwindow.h"


namespace Ui {
class AdminMainWindow;
}


class AdminMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
    ~AdminMainWindow();

private slots:

    void on_addDoctorSaveButton_clicked();

private:
    Ui::AdminMainWindow* ui;
    QSqlTableModel *sqlTableModel;
    QSqlQueryModel *querymodel;

};

#endif // ADMINMAINWINDOW_H
