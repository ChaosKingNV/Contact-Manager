#include "databasemanager.h"
#include <QFile>

DataBaseManager::DataBaseManager() {
    dbPath = "c:/database/MyContactManager.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if(!QFile::exists(dbPath))
    {
        qDebug() << "Database file doesn't exists";

    }
    else
    {
        qDebug() << "Database file exists";
    }


    if(!db.open())
        qDebug() << "Error: Unabl to open database";
    else
        qDebug() << "Database open sucessfully!";


}

DataBaseManager::~DataBaseManager()
{
    if(db.open())
        db.close();
}

DataBaseManager &DataBaseManager::instance()
{
    static DataBaseManager instance;
    return instance;
}



bool DataBaseManager::openDatabase()
{
    if(!db.open())
    {
        qDebug() << "Error Database not opened!";
        return false;
    }

    return true;
}

void DataBaseManager::closeDatabase()
{
    if(db.open())
        db.close();
}

