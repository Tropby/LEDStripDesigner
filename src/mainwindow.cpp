#include "video.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollBar>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QInputDialog>

#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(0, 0, 200 + 300 * 40, 200 + 300 * 40)
    , dialogLog(&comPort)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->verticalScrollBar()->setSliderPosition(1);
    ui->graphicsView->horizontalScrollBar()->setSliderPosition(1);

    connect(&timer, &QTimer::timeout, this, &MainWindow::timeout);

    colorButtons.append(ui->toolButtonColor1);
    colorButtons.append(ui->toolButtonColor2);
    colorButtons.append(ui->toolButtonColor3);
    colorButtons.append(ui->toolButtonColor4);
    colorButtons.append(ui->toolButtonColor5);
    colorButtons.append(ui->toolButtonColor6);
    colorButtons.append(ui->toolButtonColor7);
    colorButtons.append(ui->toolButtonColor8);

    ButtonColor(Qt::red, ui->toolButtonColor1);
    ButtonColor(Qt::blue, ui->toolButtonColor2);
    ButtonColor(Qt::green, ui->toolButtonColor3);
    ButtonColor(QColor(0xFF, 0xFF, 0x00), ui->toolButtonColor4);
    ButtonColor(QColor(0xFF, 0x00, 0xFF), ui->toolButtonColor5);
    ButtonColor(QColor(0x00, 0xFF, 0xFF), ui->toolButtonColor6);
    ButtonColor(QColor(0xFF, 0xFF, 0xFF), ui->toolButtonColor7);
    ButtonColor(Qt::black, ui->toolButtonColor8);

    for( int i = 0; i < 300; i++ )
    {
        QGraphicsSimpleTextItem* gst = new QGraphicsSimpleTextItem(QString().sprintf("%03d", i+1));
        gst->setPos(70 + i * 40 + 5, 50);
        if( (i+1) % 10 == 0 )
        {
            QFont f;
            f.setBold(true);
            gst->setFont(f);
        }
        scene.addItem(gst);

        gst = new QGraphicsSimpleTextItem(QString().sprintf("%03d", i+1));
        gst->setPos(5, 75 + i * 40);
        if( (i+1) % 10 == 0 )
        {
            QFont f;
            f.setBold(true);
            gst->setFont(f);
        }
        scene.addItem(gst);

    }

    setFrameCount(20);

    for( int i = 0; i < 256; i++ )
    {
        QString pn = QString().sprintf("\\\\.\\COM%d", i);
        QSerialPort p;
        p.setPortName(pn);
        if( p.open(QIODevice::ReadWrite) )
        {
            p.close();
            ui->comboBoxComPort->addItem(pn);
        }
    }
    timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonColor(QColor color, QToolButton* button)
{
    QPixmap px(20, 20);
    px.fill(color);
    button->setIcon(px);
    connect(button, &QToolButton::clicked, this, &MainWindow::toolButtonColor_clicked);
}

void MainWindow::setTimes(int time)
{
    for( auto i : scene.selectedItems() )
    {
        if( i->type() == QGraphicsTextItem::Type)
        {
            QGraphicsTextItem* r = static_cast<QGraphicsTextItem*>(i);

            for( auto f : frames )
            {
                QGraphicsTextItem* rf = f->getShowTime();
                if( rf == r )
                {
                    f->setTime(time);
                }
            }
        }
    }
}

void MainWindow::setLEDCount(int count)
{


    for( auto f : frames )
    {
        f->showLedCount(count);
    }
}

void MainWindow::openComPort()
{

}

void MainWindow::on_actionExport_triggered()
{
    Video video;
    for( auto f : frames )
    {
        video.addFrame(f);
    }
    video.setLEDCount( ui->spinBoxLEDCount->value() );
    video.render();    

    QString filename = QFileDialog::getSaveFileName(this,
            tr("Export Animation"), "",
            tr("Rendered Animation Video (*.ALC);;All Files (*)"));

    video.save(filename);
}

void MainWindow::on_toolButtonTime1_clicked()
{
    setTimes(30);
}

void MainWindow::on_toolButtonTime2_clicked()
{
    setTimes(15);
}


void MainWindow::on_toolButtonTime3_clicked()
{
    setTimes(30 / 4);
}

void MainWindow::on_toolButtonTime4_clicked()
{
    setTimes(3);
}

void MainWindow::setFrameCount(int count)
{
    while( ui->comboBoxCurrentFrame->count() > count )
        ui->comboBoxCurrentFrame->removeItem(ui->comboBoxCurrentFrame->count()-1);
    while( ui->comboBoxCurrentFrame->count() < count )
        ui->comboBoxCurrentFrame->addItem("Frame " + QString::number(ui->comboBoxCurrentFrame->count()+1));

    while( frames.size() > count )
    {
        Frame * f = frames.back();
        for( int j = 0; j < f->getLEDCount(); j++ )
        {
            QGraphicsRectItem* r = f->getGraphicsItem(j);
            scene.removeItem(r);
        }
        scene.removeItem(f->getShowTime());
        deletedFrames.append(f);
        frames.pop_back();
    }

    while( frames.size() < count )
    {
        if( deletedFrames.size() )
        {
            Frame * f = deletedFrames.back();
            for( int j = 0; j < f->getLEDCount(); j++ )
            {
                QGraphicsRectItem* r = f->getGraphicsItem(j);
                scene.addItem(r);
            }
            scene.addItem(f->getShowTime());


            frames.append(f);
            deletedFrames.pop_back();
        }
        else
        {
            Frame * f = new Frame(300);
            frames.append(f);

            f->showLedCount(ui->spinBoxLEDCount->value());

            QGraphicsTextItem* t = f->getShowTime();
            scene.addItem(t);
            t->setPos(30, frames.size()*40 + 30);

            for( int j = 0; j < f->getLEDCount(); j++ )
            {
                QGraphicsRectItem* r = f->getGraphicsItem(j);
                scene.addItem(r);
                r->setRect(j*40 + 70, frames.size()*40 + 30, 30, 30);
                r->setBrush(Qt::black);
            }
        }
    }

    setLEDCount(ui->spinBoxLEDCount->value());
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    setFrameCount(arg1);
}

void MainWindow::on_actionSave_triggered()
{
    QJsonDocument doc;
    QJsonObject obj;

    QJsonArray frames;
    for( auto f : this->frames )
    {
        frames.append(f->save());
    }
    obj["frames"] = frames;
    obj["ledCount"] = ui->spinBoxLEDCount->value();
    obj["saveDate"] = QDateTime::currentDateTime().toString();
    doc.setObject(obj);

    QString filename = QFileDialog::getSaveFileName(this,
            tr("Save Animation"), "",
            tr("Animation (*.json.ani);;All Files (*)"));
    QFile f;
    f.setFileName(filename);
    if( f.open(QIODevice::WriteOnly) )
    {
        f.write(doc.toJson());
        f.close();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Can not save file!");
    }
}

void MainWindow::on_action_ffnen_triggered()
{
    QJsonDocument doc;

    QString filename = QFileDialog::getOpenFileName(this,
            tr("Save Animation"), "",
            tr("Animation (*.json.ani);;All Files (*)"));
    QFile f;
    f.setFileName(filename);
    if( f.open(QIODevice::ReadOnly) )
    {
        doc = QJsonDocument::fromJson(f.readAll());
        f.close();

        QJsonObject obj = doc.object();

        ui->spinBoxLEDCount->setValue(obj["ledCount"].toInt());

        QJsonArray frames = obj["frames"].toArray();
        ui->spinBox->setValue(frames.count());

        setFrameCount(frames.size());
        for( int i = 0; i < frames.size(); i++ )
        {
            this->frames[i]->load(frames[i].toObject());
        }
        doc.setObject(obj);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Can not open file!");
    }
}

void MainWindow::on_actionNeu_triggered()
{
    setFrameCount(0);
    ui->spinBox->setValue(1);
    deletedFrames.clear();
    setFrameCount(1);
}

void MainWindow::on_actionBeenden_triggered()
{
    QApplication::quit();
}

void MainWindow::on_spinBoxLEDCount_valueChanged(int arg1)
{
    setLEDCount(arg1);
}

void MainWindow::on_comboBoxComPort_currentTextChanged(const QString &arg1)
{
    comPort.close();
    comPort.setPortName(arg1);
    comPort.setBaudRate(115200);
    if(!comPort.open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this, "ERROR", "Can not open Serial Port! " + comPort.errorString());
    }
}

void MainWindow::on_toolButtonLiveMode_clicked()
{
    if( ui->toolButtonLiveMode->toolTip().compare("PLAY") )
    {
        ui->toolButtonLiveMode->setIcon(QPixmap(":/icons/res/play.png"));
        ui->toolButtonLiveMode->setToolTip("PLAY");
    }
    else
    {
        ui->toolButtonLiveMode->setIcon(QPixmap(":/icons/res/pause.png"));
        ui->toolButtonLiveMode->setToolTip("STOP");
    }
}

void MainWindow::timeout()
{

    char data[1024];
    QByteArray b;
    b.append(0x02);
    comPort.write(b);
    frames[ui->comboBoxCurrentFrame->currentIndex()]->render();
    frames[ui->comboBoxCurrentFrame->currentIndex()]->getRawData(reinterpret_cast<uint8_t*>(data), 1024);
    comPort.write(data, 1024);

    timer.setInterval(
        frames[ui->comboBoxCurrentFrame->currentIndex()]->getTime() / 30.0 * 1000 );

    qDebug() << "Set Timeout Interval" << frames[ui->comboBoxCurrentFrame->currentIndex()]->getTime() / 30.0 * 1000;

    if( ui->toolButtonLiveMode->toolTip().compare("PLAY") )
    {
        if(ui->comboBoxCurrentFrame->currentIndex() == ui->comboBoxCurrentFrame->count()-1)
            ui->comboBoxCurrentFrame->setCurrentIndex(0 );
        else
            ui->comboBoxCurrentFrame->setCurrentIndex(ui->comboBoxCurrentFrame->currentIndex()+1);
    }

}

void MainWindow::toolButtonColor_clicked()
{
    QToolButton* tb = static_cast<QToolButton*>(QObject::sender());

    QPixmap px = tb->icon().pixmap(QSize(32,32));
    QImage img(px.toImage());
    QRgb rgb = img.pixel(1, 1);
    QColor color(rgb);

    for( auto i : scene.selectedItems() )
    {
        if( i->type() == QGraphicsRectItem::Type)
        {
            QGraphicsRectItem* r = reinterpret_cast<QGraphicsRectItem*>(i);
            r->setBrush(color);
        }
    }
}

void MainWindow::on_toolButtonSerialLog_clicked()
{
    dialogLog.show();
}

void MainWindow::on_toolButtonNextFrame_clicked()
{
    if(ui->comboBoxCurrentFrame->currentIndex() == ui->comboBoxCurrentFrame->count()-1)
        ui->comboBoxCurrentFrame->setCurrentIndex(0 );
    else
        ui->comboBoxCurrentFrame->setCurrentIndex(ui->comboBoxCurrentFrame->currentIndex()+1);
    timer.setInterval(100);
}


void MainWindow::on_toolButton_clicked()
{
    if(ui->comboBoxCurrentFrame->currentIndex() == 0)
        ui->comboBoxCurrentFrame->setCurrentIndex(ui->comboBoxCurrentFrame->count()-1 );
    else
        ui->comboBoxCurrentFrame->setCurrentIndex(ui->comboBoxCurrentFrame->currentIndex()-1);
    timer.setInterval(100);
}

void MainWindow::on_actionFarben_triggered()
{
    QList<QColor> colors;

    for( auto btn : colorButtons )
    {
        QPixmap px = btn->icon().pixmap(QSize(32,32));
        QImage img(px.toImage());
        QRgb rgb = img.pixel(1, 1);
        QColor color(rgb);
        colors.append(color);
    }

    DialogColors dc(colors);
    if( dc.exec() == DialogColors::Accepted )
    {
        colors = dc.getColors();
        for( int i = 0; i < colors.count(); i++ )
        {
            ButtonColor(colors[i], colorButtons[i]);
        }
    }
}

void MainWindow::on_toolButtonTimeX_clicked()
{
    QInputDialog id;
    id.setTextValue("1.0");
    id.setLabelText("Zeit in Sekunden:");
    id.setWindowTitle("Zeiteingabe");
    if( id.exec() == QInputDialog::Accepted )
    {
        setTimes(id.textValue().replace(",", ".").toDouble() * 30);
    }
}
