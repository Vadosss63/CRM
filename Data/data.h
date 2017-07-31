#ifndef DATA_H
#define DATA_H

#include <QList>
#include <QMap>
#include <QString>

class Data
{
public:
    Data();
    ~Data();

    void AddData(QString nameFeild, QString content);
    QString GetValueFeild(QString nameFeild);
    QMap<QString, QString> Datas() const;
    int CountData();
    QList<QString> GetListFeildName() const;

private:
    // хранимая информация
    QMap<QString, QString> m_Datas;
    // необходим для учета порядка добавления записей
    // в карту данных
    QList<QString> m_ListFeildName;
};

#endif // DATA_H
