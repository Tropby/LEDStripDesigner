#ifndef DIALOGLOG_H
#define DIALOGLOG_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class DialogLog;
}

class DialogLog : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLog(QSerialPort * serialPort, QWidget *parent = nullptr);
    ~DialogLog();

private slots:
    void onSerialData();

private:
    Ui::DialogLog *ui;
    QSerialPort * serialPort;
};

#endif // DIALOGLOG_H
