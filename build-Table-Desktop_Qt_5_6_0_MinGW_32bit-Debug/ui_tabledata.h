/********************************************************************************
** Form generated from reading UI file 'tabledata.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEDATA_H
#define UI_TABLEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableVRLI
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *TableVRLI)
    {
        if (TableVRLI->objectName().isEmpty())
            TableVRLI->setObjectName(QStringLiteral("TableVRLI"));
        TableVRLI->resize(274, 437);
        gridLayout = new QGridLayout(TableVRLI);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        retranslateUi(TableVRLI);

        QMetaObject::connectSlotsByName(TableVRLI);
    } // setupUi

    void retranslateUi(QWidget *TableVRLI)
    {
        TableVRLI->setWindowTitle(QApplication::translate("TableVRLI", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class TableVRLI: public Ui_TableVRLI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEDATA_H
