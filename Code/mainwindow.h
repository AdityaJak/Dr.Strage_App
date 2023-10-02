#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class doctor_main;
class hospitalAdminMain;
class DoctorMainWindow;
class systemAdminMain;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ClearUsernamePassword();

private slots:
    void on_loginButton_clicked();
    void on_pushButton_clicked();

signals:
    void sendData(QStringList);

private:
    Ui::MainWindow *ui;
    DoctorMainWindow *doctor_main_window = nullptr;
    hospitalAdminMain *hospitalAdminMain_window = nullptr;
    systemAdminMain *systemAdminMain_window = nullptr;

};
#endif // MAINWINDOW_H
