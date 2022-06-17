/********************************************************************************
** Form generated from reading UI file 'dialoglog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOG_H
#define UI_DIALOGLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogLog
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;

    void setupUi(QDialog *DialogLog)
    {
        if (DialogLog->objectName().isEmpty())
            DialogLog->setObjectName(QString::fromUtf8("DialogLog"));
        DialogLog->resize(798, 351);
        verticalLayout = new QVBoxLayout(DialogLog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(DialogLog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);


        retranslateUi(DialogLog);

        QMetaObject::connectSlotsByName(DialogLog);
    } // setupUi

    void retranslateUi(QDialog *DialogLog)
    {
        DialogLog->setWindowTitle(QCoreApplication::translate("DialogLog", "UART Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogLog: public Ui_DialogLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOG_H
