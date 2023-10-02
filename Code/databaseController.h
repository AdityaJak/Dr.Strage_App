#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <string>
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>


class databaseController {
public :
    QSqlDatabase db;

    bool initDatabase(){
        db = QSqlDatabase::addDatabase("QMYSQL");
        qDebug() << db;
        db.setHostName("drstrangev2.chxbl7ovxsi4.us-east-1.rds.amazonaws.com");
        db.setDatabaseName("drstrangev0");
        db.setUserName("root");
        db.setPassword("METCS673*!DRSTRANGE2022!xyZtV0!");
        qDebug() << db;
        if(db.open()){
            qDebug() << "ok";
            qDebug() << db;
        }
        if(!db.open()){
            qDebug() << "Not ok";
        }
        return db.open();
    }


    void closeDatabase(){
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }


private:



};


#endif // DATABASECONTROLLER_H
