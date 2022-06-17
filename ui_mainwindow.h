/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExport;
    QAction *actionSave;
    QAction *action_ffnen;
    QAction *actionBeenden;
    QAction *actionNeu;
    QAction *actionFarben;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelFrames;
    QSpinBox *spinBox;
    QLabel *labelLEDs;
    QSpinBox *spinBoxLEDCount;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QComboBox *comboBoxComPort;
    QLabel *label_2;
    QToolButton *toolButton;
    QComboBox *comboBoxCurrentFrame;
    QToolButton *toolButtonLiveMode;
    QToolButton *toolButtonNextFrame;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButtonTimeX;
    QToolButton *toolButtonTime1;
    QToolButton *toolButtonTime2;
    QToolButton *toolButtonTime3;
    QToolButton *toolButtonTime4;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButtonColor1;
    QToolButton *toolButtonColor2;
    QToolButton *toolButtonColor3;
    QToolButton *toolButtonColor4;
    QToolButton *toolButtonColor5;
    QToolButton *toolButtonColor6;
    QToolButton *toolButtonColor7;
    QToolButton *toolButtonColor8;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButtonSerialLog;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QMenu *menuBearbeiten;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1228, 590);
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        action_ffnen = new QAction(MainWindow);
        action_ffnen->setObjectName(QString::fromUtf8("action_ffnen"));
        actionBeenden = new QAction(MainWindow);
        actionBeenden->setObjectName(QString::fromUtf8("actionBeenden"));
        actionNeu = new QAction(MainWindow);
        actionNeu->setObjectName(QString::fromUtf8("actionNeu"));
        actionFarben = new QAction(MainWindow);
        actionFarben->setObjectName(QString::fromUtf8("actionFarben"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        labelFrames = new QLabel(centralwidget);
        labelFrames->setObjectName(QString::fromUtf8("labelFrames"));

        horizontalLayout->addWidget(labelFrames);

        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(80, 30));
        spinBox->setMaximumSize(QSize(80, 50));
        spinBox->setMinimum(1);
        spinBox->setMaximum(300);
        spinBox->setValue(20);

        horizontalLayout->addWidget(spinBox);

        labelLEDs = new QLabel(centralwidget);
        labelLEDs->setObjectName(QString::fromUtf8("labelLEDs"));

        horizontalLayout->addWidget(labelLEDs);

        spinBoxLEDCount = new QSpinBox(centralwidget);
        spinBoxLEDCount->setObjectName(QString::fromUtf8("spinBoxLEDCount"));
        spinBoxLEDCount->setMinimumSize(QSize(80, 30));
        spinBoxLEDCount->setMaximumSize(QSize(80, 50));
        spinBoxLEDCount->setMinimum(2);
        spinBoxLEDCount->setMaximum(300);
        spinBoxLEDCount->setValue(300);

        horizontalLayout->addWidget(spinBoxLEDCount);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBoxComPort = new QComboBox(centralwidget);
        comboBoxComPort->setObjectName(QString::fromUtf8("comboBoxComPort"));
        comboBoxComPort->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(comboBoxComPort);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setMinimumSize(QSize(30, 30));
        toolButton->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/last.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);

        horizontalLayout->addWidget(toolButton);

        comboBoxCurrentFrame = new QComboBox(centralwidget);
        comboBoxCurrentFrame->setObjectName(QString::fromUtf8("comboBoxCurrentFrame"));
        comboBoxCurrentFrame->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(comboBoxCurrentFrame);

        toolButtonLiveMode = new QToolButton(centralwidget);
        toolButtonLiveMode->setObjectName(QString::fromUtf8("toolButtonLiveMode"));
        toolButtonLiveMode->setMinimumSize(QSize(30, 30));
        toolButtonLiveMode->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/res/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonLiveMode->setIcon(icon1);

        horizontalLayout->addWidget(toolButtonLiveMode);

        toolButtonNextFrame = new QToolButton(centralwidget);
        toolButtonNextFrame->setObjectName(QString::fromUtf8("toolButtonNextFrame"));
        toolButtonNextFrame->setMinimumSize(QSize(30, 30));
        toolButtonNextFrame->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/res/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonNextFrame->setIcon(icon2);

        horizontalLayout->addWidget(toolButtonNextFrame);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        toolButtonTimeX = new QToolButton(centralwidget);
        toolButtonTimeX->setObjectName(QString::fromUtf8("toolButtonTimeX"));
        toolButtonTimeX->setMinimumSize(QSize(50, 50));
        toolButtonTimeX->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonTimeX);

        toolButtonTime1 = new QToolButton(centralwidget);
        toolButtonTime1->setObjectName(QString::fromUtf8("toolButtonTime1"));
        toolButtonTime1->setMinimumSize(QSize(50, 50));
        toolButtonTime1->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonTime1);

        toolButtonTime2 = new QToolButton(centralwidget);
        toolButtonTime2->setObjectName(QString::fromUtf8("toolButtonTime2"));
        toolButtonTime2->setMinimumSize(QSize(50, 0));
        toolButtonTime2->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonTime2);

        toolButtonTime3 = new QToolButton(centralwidget);
        toolButtonTime3->setObjectName(QString::fromUtf8("toolButtonTime3"));
        toolButtonTime3->setMinimumSize(QSize(50, 50));
        toolButtonTime3->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonTime3);

        toolButtonTime4 = new QToolButton(centralwidget);
        toolButtonTime4->setObjectName(QString::fromUtf8("toolButtonTime4"));
        toolButtonTime4->setMinimumSize(QSize(50, 50));
        toolButtonTime4->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonTime4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        toolButtonColor1 = new QToolButton(centralwidget);
        toolButtonColor1->setObjectName(QString::fromUtf8("toolButtonColor1"));
        toolButtonColor1->setMinimumSize(QSize(50, 50));
        toolButtonColor1->setMaximumSize(QSize(50, 50));
        toolButtonColor1->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(toolButtonColor1);

        toolButtonColor2 = new QToolButton(centralwidget);
        toolButtonColor2->setObjectName(QString::fromUtf8("toolButtonColor2"));
        toolButtonColor2->setMinimumSize(QSize(50, 50));
        toolButtonColor2->setMaximumSize(QSize(50, 50));
        toolButtonColor2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(toolButtonColor2);

        toolButtonColor3 = new QToolButton(centralwidget);
        toolButtonColor3->setObjectName(QString::fromUtf8("toolButtonColor3"));
        toolButtonColor3->setMinimumSize(QSize(50, 50));
        toolButtonColor3->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonColor3);

        toolButtonColor4 = new QToolButton(centralwidget);
        toolButtonColor4->setObjectName(QString::fromUtf8("toolButtonColor4"));
        toolButtonColor4->setMinimumSize(QSize(50, 50));
        toolButtonColor4->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonColor4);

        toolButtonColor5 = new QToolButton(centralwidget);
        toolButtonColor5->setObjectName(QString::fromUtf8("toolButtonColor5"));
        toolButtonColor5->setMinimumSize(QSize(50, 50));
        toolButtonColor5->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonColor5);

        toolButtonColor6 = new QToolButton(centralwidget);
        toolButtonColor6->setObjectName(QString::fromUtf8("toolButtonColor6"));
        toolButtonColor6->setMinimumSize(QSize(50, 50));
        toolButtonColor6->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonColor6);

        toolButtonColor7 = new QToolButton(centralwidget);
        toolButtonColor7->setObjectName(QString::fromUtf8("toolButtonColor7"));
        toolButtonColor7->setMinimumSize(QSize(50, 50));
        toolButtonColor7->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonColor7);

        toolButtonColor8 = new QToolButton(centralwidget);
        toolButtonColor8->setObjectName(QString::fromUtf8("toolButtonColor8"));
        toolButtonColor8->setMinimumSize(QSize(50, 50));
        toolButtonColor8->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(toolButtonColor8);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        toolButtonSerialLog = new QToolButton(centralwidget);
        toolButtonSerialLog->setObjectName(QString::fromUtf8("toolButtonSerialLog"));
        toolButtonSerialLog->setMinimumSize(QSize(50, 50));
        toolButtonSerialLog->setMaximumSize(QSize(50, 50));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/res/log.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonSerialLog->setIcon(icon3);
        toolButtonSerialLog->setIconSize(QSize(32, 32));

        horizontalLayout_2->addWidget(toolButtonSerialLog);


        verticalLayout->addLayout(horizontalLayout_2);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);

        verticalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1228, 21));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        menuBearbeiten = new QMenu(menubar);
        menuBearbeiten->setObjectName(QString::fromUtf8("menuBearbeiten"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDatei->menuAction());
        menubar->addAction(menuBearbeiten->menuAction());
        menuDatei->addAction(actionNeu);
        menuDatei->addAction(action_ffnen);
        menuDatei->addAction(actionSave);
        menuDatei->addSeparator();
        menuDatei->addAction(actionExport);
        menuDatei->addSeparator();
        menuDatei->addAction(actionBeenden);
        menuBearbeiten->addAction(actionFarben);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "LED Strip Designer", nullptr));
        actionExport->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Speichen", nullptr));
        action_ffnen->setText(QCoreApplication::translate("MainWindow", "\303\226ffnen", nullptr));
        actionBeenden->setText(QCoreApplication::translate("MainWindow", "Beenden", nullptr));
        actionNeu->setText(QCoreApplication::translate("MainWindow", "Neu", nullptr));
        actionFarben->setText(QCoreApplication::translate("MainWindow", "Farben", nullptr));
        labelFrames->setText(QCoreApplication::translate("MainWindow", "Frames", nullptr));
        labelLEDs->setText(QCoreApplication::translate("MainWindow", "LED-Anzahl", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Live Mode Port", nullptr));
        label_2->setText(QString());
        toolButton->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonLiveMode->setToolTip(QCoreApplication::translate("MainWindow", "PLAY", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonLiveMode->setText(QString());
        toolButtonNextFrame->setText(QString());
        toolButtonTimeX->setText(QCoreApplication::translate("MainWindow", "X s", nullptr));
        toolButtonTime1->setText(QCoreApplication::translate("MainWindow", "1 s", nullptr));
        toolButtonTime2->setText(QCoreApplication::translate("MainWindow", "0,5 s", nullptr));
        toolButtonTime3->setText(QCoreApplication::translate("MainWindow", "0.2 s", nullptr));
        toolButtonTime4->setText(QCoreApplication::translate("MainWindow", "0,1 s", nullptr));
        toolButtonColor1->setText(QString());
        toolButtonColor2->setText(QString());
        toolButtonColor3->setText(QString());
        toolButtonColor4->setText(QString());
        toolButtonColor5->setText(QString());
        toolButtonColor6->setText(QString());
        toolButtonColor7->setText(QString());
        toolButtonColor8->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonSerialLog->setToolTip(QCoreApplication::translate("MainWindow", "UART Log", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonSerialLog->setText(QString());
        menuDatei->setTitle(QCoreApplication::translate("MainWindow", "Datei", nullptr));
        menuBearbeiten->setTitle(QCoreApplication::translate("MainWindow", "Bearbeiten", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
