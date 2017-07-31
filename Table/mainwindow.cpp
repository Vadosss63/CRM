#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TableData* table = new TableData();

    Data* data = new Data();
    data->AddData("Имя", "Иван");
    data->AddData("Фамилия", "Иванов");
    data->AddData("Отчество", "Иванович");
    data->AddData("Дата Рождения", "10.11.1991");
    data->AddData("Гражданство", "РФ");
    data->AddData("Коментарий", "Создал файл");

    for (int i = 0; i < 100; ++i) {
        table->AddRow(data);
    }
    setCentralWidget(table);
}

MainWindow::~MainWindow()
{
    delete ui;
}
