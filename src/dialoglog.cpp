#include "dialoglog.h"
#include "ui_dialoglog.h"

#include <QDateTime>

DialogLog::DialogLog(QSerialPort * serialPort, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLog),
    serialPort(serialPort)
{
    ui->setupUi(this);
    connect(serialPort, &QSerialPort::readyRead, this, &DialogLog::onSerialData);
}

DialogLog::~DialogLog()
{
    delete ui;
}

void DialogLog::onSerialData()
{
    while( ui->listWidget->count() > 100 )
        ui->listWidget->takeItem(0);

    while( serialPort->canReadLine() )
    {
        ui->listWidget->addItem( QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss") + ": " + serialPort->readLine().trimmed());
    }
    ui->listWidget->scrollToBottom();
}
