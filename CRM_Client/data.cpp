#include "data.h"

Data::Data(){}

Data::~Data(){}

QString Data::GetData(QString nameField)
{
    return m_Datas[nameField];
}

void Data::SetData(QString nameField, QString content)
{
    m_Datas[nameField] = content;
}

QMap<QString, QString> Data::Datas() const
{
    return m_Datas;
}

#include "data.h"
