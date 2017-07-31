#ifndef SQLMODULE_H
#define SQLMODULE_H

#include <QObject>
#include <QList>
#include <QtSql/qsql.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqldatabase.h>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QFile>
#include <QDate>
#include <QDebug>
#include "../Data/data.h"


//Макросы, задающие БД
#define DATABASE_HOSTNAME "localhost"
#define DATABASE_NAME "BDClient"

// выполнить тест класса
class SQLmodule : public QObject
{
    Q_OBJECT
public:
    explicit SQLmodule(QObject *parent = 0);
    ~SQLmodule();
    // методы работы с базой
    void ConnectToDB();// выполнить проверку
    // Вставка данных
    bool InsertDatas(QString tableName, Data datas);// выполнить проверку
    // Удаление данных
    bool RemoveData(QString tableName, QString feildName, QString condition);// выполнить проверку
    // Изменение данных по одному условию
    bool ChangeData(QString tableName, QString feildName, QString condition, Data datas);// выполнить проверку
    // Изменение данных по нескольким условиям условию
    bool ChangeData(QString tableName, QString conditions, Data datas);// выполнить проверку
    // возврящает строки полученые в результате поиска
    QList<Data> GetDatas(QString tableName, QString fieldName, QVariant content);
    // Cоздание файла БД
    bool CreateBDFile();

private:
    // объект базы данных
    QSqlDatabase m_db;
    // методы работы с БД
    bool OpenDB();
    void CloseDB();

    QList<QString> m_feildsName;
};

#endif // SQLMODULE_H
