#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QMap>

// Класс выполняет хранения данных
// выполняет роль динамически расширяемого поля
class Data
{
public:
    Data();
    ~Data();
    // Возвращает Значение поля по ключу
    QString GetData(QString nameField);
    // Производит изменения поля или создание,
    // если поля не существует
    void SetData(QString nameField, QString content);
    // возврящает список с данными
    QMap<QString, QString> Datas() const;

private:
    QMap<QString, QString> m_Datas;
};



#endif // DATA_H
