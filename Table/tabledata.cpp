#include "tabledata.h"

TableModel::TableModel(QObject *pr): QAbstractTableModel(pr){}


int TableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_listItem.count();
}

int TableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return m_nameFeilds.count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::TextAlignmentRole:
        return int(Qt::AlignCenter);

    case Qt::DisplayRole: // Возвращает значенияполя
    {
        return m_listItem.at(index.row())->GetValueFeild(headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString());
    }
    default:
        return QVariant();
    }
}



QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        switch (role) {
        case Qt::DisplayRole:
            return m_nameFeilds[section];

        case Qt::TextAlignmentRole:
            return int(Qt::AlignCenter);

        case Qt::ToolTipRole:
        {
            if(section == 0)
                return QString("Номер цели");

            if(section == 1)
                return QString("Пеленг цели");

            if(section == 2)
                return QString("Дальность до цели");

            if(section == 3)
                return QString("Скорость цели");
        }
        default:
            return QVariant();
        }
    }
    return QVariant();
}

void TableModel::addItemData(Data* datas)
{
    if(m_listItem.empty()) // выполняем построение таблицы
    {
        m_nameFeilds.clear();
        m_nameFeilds = datas->GetListFeildName();
    }

    beginInsertRows(QModelIndex(), 0, 0);
    m_listItem.append(datas);
    endInsertRows();

    //если данные есть в списке
    //            dataChanged(index(i, 0), index(i, 4));


}

void TableModel::RemoveItem()
{
    //    beginRemoveRows(QModelIndex(), m_listItem.count() - 1, m_listItem.count() - 1);
    //    endRemoveRows();
}

void TableModel::SelectionRow()
{
    emit SelectRow(0);
}

TableData::TableData(QWidget *parent) :
    QTableView(parent)
{
    CreateTable();
}

TableData::~TableData(){}

void TableData::AddRow(Data* data)
{
    return m_model.addItemData(data);
}

void TableData::CreateTable()
{
    setModel(&m_model);
    setStyleSheet("QHeaderView::section {color: #222222; background-color: qlineargradient(x1:0, y1:1, x2:0, y2:0, "
                  "stop:0  #9db1cc, "
                  "stop:0.6 #a2a2d0,"
                  "stop:1 #9db1cc ); border: 1px solid #b5b8b1;}"
                  "* {color: #222222; background-color: #f0f8ff; border: 1px solid #b5b8b1; gridline-color:#b5b8b1;}"
                  "QTableView:item:selected{ background-color: qlineargradient(x1:0, y1:1, x2:0, y2:0, "
                  "stop:0  #9db1cc, "
                  "stop:0.6 #a2a2d0,"
                  "stop:1 #9db1cc );}"
                  "QScrollBar:vertical {"
                  "border: 2px solid #b5b8b1;"
                  "background: #f0f8ff;"
                  "width: 15px;"
                  "margin: 22px 0 22px 0;}"
                  "QScrollBar::handle:vertical {"
                  "background: #555555;"
                  "min-height: 20px;}"
                  "QScrollBar::add-line:vertical {"
                  "border: 2px solid #b5b8b1;"
                  "background: #444444;"
                  "height: 20px;"
                  "subcontrol-position: bottom;"
                  "subcontrol-origin: margin;}"
                  "QScrollBar::sub-line:vertical {"
                  "border: 2px solid #b5b8b1;"
                  "background: #444444;"
                  "height: 20px;"
                  "subcontrol-position: top;"
                  "subcontrol-origin: margin;}"
                  "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                  "border: 2px solid #b5b8b1;"
                  "width: 3px;"
                  "height: 3px;"
                  "background: white;}"
                  "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                  "background: none;}");

    horizontalHeader()->setStretchLastSection(true);
    //    setFixedWidth(300);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}


