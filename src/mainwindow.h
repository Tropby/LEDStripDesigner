#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "frame.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QToolButton>
#include <QColor>
#include <QSerialPort>
#include <QTimer>
#include "dialoglog.h"
#include "dialogcolors.h"

#include "config.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExport_triggered();
    void on_toolButtonTime1_clicked();
    void on_toolButtonTime2_clicked();
    void on_toolButtonTime3_clicked();
    void on_toolButtonTime4_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_actionSave_triggered();

    void on_action_ffnen_triggered();

    void on_actionNeu_triggered();

    void on_actionBeenden_triggered();

    void on_spinBoxLEDCount_valueChanged(int arg1);

    void on_comboBoxComPort_currentTextChanged(const QString &arg1);

    void on_toolButtonLiveMode_clicked();

    void timeout();

    void toolButtonColor_clicked();

    void on_toolButtonSerialLog_clicked();

    void on_toolButtonNextFrame_clicked();

    void on_toolButton_clicked();

    void on_actionFarben_triggered();

    void on_toolButtonTimeX_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene scene;
    QList<Frame*> frames;
    QList<Frame*> deletedFrames;
    QList<QGraphicsSimpleTextItem*> topGrid;

    QSerialPort comPort;
    QTimer timer;

    DialogLog dialogLog;
    QList<QToolButton*> colorButtons;

    void setFrameCount(int count);

    void ButtonColor(QColor color, QToolButton* button);
    void setTimes(int time);
    void setLEDCount(int count);

    void openComPort();

};
#endif // MAINWINDOW_H
