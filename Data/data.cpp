#include "data.h"

Data::Data(){}

Data::~Data(){}

void Data::AddData(QString nameFeild, QString content)
{
    if(!m_Datas.contains(nameFeild))
        m_ListFeildName.append(nameFeild);

    m_Datas[nameFeild] = content;
}

QString Data::GetValueFeild(QString nameFeild)
{
    return m_Datas[nameFeild];
}

QMap<QString, QString> Data::Datas() const
{
    return m_Datas;
}

int Data::CountData()
{
    return  m_Datas.count();
}

QList<QString> Data::GetListFeildName() const
{
    return m_ListFeildName;
}
