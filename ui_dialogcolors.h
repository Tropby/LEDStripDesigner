/********************************************************************************
** Form generated from reading UI file 'dialogcolors.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCOLORS_H
#define UI_DIALOGCOLORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogColors
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogColors)
    {
        if (DialogColors->objectName().isEmpty())
            DialogColors->setObjectName(QString::fromUtf8("DialogColors"));
        DialogColors->resize(527, 436);
        verticalLayout = new QVBoxLayout(DialogColors);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(DialogColors);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        pushButton = new QPushButton(DialogColors);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(DialogColors);

        QMetaObject::connectSlotsByName(DialogColors);
    } // setupUi

    void retranslateUi(QDialog *DialogColors)
    {
        DialogColors->setWindowTitle(QCoreApplication::translate("DialogColors", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("DialogColors", "speichern", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogColors: public Ui_DialogColors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCOLORS_H
