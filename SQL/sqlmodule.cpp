#include "sqlmodule.h"


SQLmodule::SQLmodule(QObject *parent) :
    QObject(parent){}

SQLmodule::~SQLmodule(){}

void SQLmodule::ConnectToDB()
{
    //  выполняем проверку наличия БД
    OpenDB();
}

bool SQLmodule::InsertDatas(QString tableName, Data datas)
{
    QString str_insert = QString("INSERT INTO %1 ( ").arg(tableName);

    foreach(auto feildName, m_feildsName)
    {
        str_insert += QString("%1, ").arg(feildName);
    }
    str_insert += QString(") VALUES (");

    foreach(auto feildName, m_feildsName)
    {
        str_insert += QString("%1, ").arg(datas.GetValueFeild(feildName));
    }

    str_insert += QString(" )");

    QSqlQuery query(str_insert);
    QSqlRecord rec = query.record();

    return true;
}

bool SQLmodule::RemoveData(QString tableName, QString feildName, QString condition)
{
    QString str_update = QString("DELETE FROM %1 WHERE %2 = %3").arg(tableName, feildName, condition);
    QSqlQuery query(str_update);
    QSqlRecord rec = query.record();
    return true;
}

bool SQLmodule::ChangeData(QString tableName, QString feildName, QString condition, Data datas)
{

    QString str_update = QString("UPDATE %1 SET ").arg(tableName);

    foreach(auto feildName, m_feildsName)
    {
        str_update += QString("%1 = '%2'").arg(feildName, datas.GetValueFeild(feildName));
        str_update += ", ";
    }
    str_update += QString(" WHERE %1 = %2").arg(feildName, condition);

    QSqlQuery query(str_update);
    QSqlRecord rec = query.record();

    return true;
}

bool SQLmodule::ChangeData(QString tableName,  QString conditions, Data datas)
{

    QString str_update = QString("UPDATE %1 SET ").arg(tableName);

    foreach(auto feildName, m_feildsName)
    {
        str_update += QString("%1 = '%2'").arg(feildName, datas.GetValueFeild(feildName));
        str_update += ", ";
    }
    str_update += QString(" WHERE %1").arg(conditions);

    QSqlQuery query(str_update);
    QSqlRecord rec = query.record();

    return true;
}


QList<Data> SQLmodule::GetDatas(QString tableName, QString fieldName, QVariant content)
{
    QList<Data> list;
    QString str_insert = QString("SELECT * FROM %1 WHERE %2 = %3").arg(tableName, fieldName, content.toString());
    QSqlQuery query(str_insert);
    QSqlRecord rec = query.record();

    // выполняем запись в массив данных
    while(query.next())
    {
        Data currentRow;
        foreach (QString feildName, m_feildsName)
        {
            currentRow.AddData(feildName, query.value(rec.indexOf(feildName)).toString());
        }

        list.push_back(currentRow);
    }
    return list;
}

bool SQLmodule::CreateBDFile()
{
    // описать команды создание файла БД
    QString str_createBD = QString("CREATE TABLE %1 (").arg(DATABASE_NAME);

    foreach(auto feildName, m_feildsName)
    {
        str_createBD += QString("'%1' varchar(255), ").arg(feildName);
    }
    str_createBD += QString(" );");
    QSqlQuery query(str_createBD);
    QSqlRecord rec = query.record();
    return true;

}

// метод открытия BD
bool SQLmodule::OpenDB()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(DATABASE_HOSTNAME);
    m_db.setDatabaseName(DATABASE_NAME);
    m_db.setUserName("root");
    if(m_db.open())
        return true;
    else
    {
        qDebug() << m_db.lastError();
        return false;
    }

}

//  закрытие BD
void SQLmodule::CloseDB()
{
    m_db.close();
}
