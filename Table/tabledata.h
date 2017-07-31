#ifndef TABLEVRLI_H
#define TABLEVRLI_H

#include <QString>
#include <QPen>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QMap>
#include <QTimer>
#include <QGraphicsPathItem>
#include "../Data/data.h"


// Класс управления данными в таблице
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject* pr = 0);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    // выполняет добавление данных
    void addItemData(Data* datas);

signals:
    void SelectRow(int row);
private slots:
    void RemoveItem();
    void SelectionRow();
private:
    // Лист данных
    QList<Data*> m_listItem;
    // Заголовки таблицы
    QList<QString> m_nameFeilds;
};

class TableData : public QTableView
{
    Q_OBJECT
public:
    explicit TableData(QWidget *parent = 0);
    ~TableData();
    void AddRow(Data *data);

private:
    void CreateTable();
    TableModel m_model;
};

#endif // TABLEVRLI_H
