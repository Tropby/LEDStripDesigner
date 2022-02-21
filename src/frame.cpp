#include "frame.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <QDebug>
#include <QBrush>
#include <QPen>

Frame::Frame(int ledCount) : ledCount(300), time(30)
{
    data = new LED[ledCount];
    items = new QGraphicsRectItem*[ledCount];

    showTime = new QGraphicsTextItem();
    showTime->setFlag(QGraphicsItem::ItemIsSelectable);

    for( int i = 0; i < ledCount; i++ )
    {
        items[i] = new QGraphicsRectItem();
        items[i]->setFlag(QGraphicsItem::ItemIsSelectable);

        if( (i+1) % 10 == 0 )
        {
            QPen p;
            p.setWidth(2);
            items[i]->setPen(p);
        }
    }
    setTime(30);
}

void Frame::showLedCount(int count)
{
    for( int i = 0; i < 300; i++ )
    {
        items[i]->hide();
    }

    for( int i = 0; i < count; i++ )
    {
        items[i]->show();
    }
}

void Frame::render()
{
    for( int i = 0; i < ledCount; i++ )
    {
        QBrush b = items[i]->brush();

        data[i].r = b.color().red();
        data[i].g = b.color().green();
        data[i].b = b.color().blue();
    }
}

uint16_t Frame::getLEDCount()
{
    return ledCount;
}

uint16_t Frame::getRawData(uint8_t *data, uint16_t maxSize)
{
    qDebug() << "LED-Data-Size: " << sizeof(LED);
    if( maxSize > sizeof(LED) * ledCount)
        maxSize = sizeof(LED) * ledCount;
    memcpy(data, this->data, maxSize);
    return maxSize;
}

QGraphicsRectItem *Frame::getGraphicsItem(int index)
{
    return items[index];
}

QGraphicsTextItem *Frame::getShowTime()
{
    return showTime;
}

void Frame::setTime(int timeInFrames)
{
    time = timeInFrames;
    showTime->setHtml(QString().sprintf("%.1f", timeInFrames / 30.0) + " s");
}

int Frame::getTime()
{
    return time;
}

QJsonObject Frame::save()
{
    QJsonObject result;
    QJsonArray ledData;
    render();
    for( int i = 0; i < ledCount; i++ )
    {
        QJsonObject led;
        led["r"] = this->data[i].r;
        led["g"] = this->data[i].g;
        led["b"] = this->data[i].b;
        ledData.append(led);
    }
    result["leds"] = ledData;
    result["time"] = time;
    return result;
}

void Frame::load(QJsonObject data)
{
    QJsonArray ledData = data["leds"].toArray();
    for( int i = 0; i < ledData.size(); i++ )
    {
        uint8_t r = ledData[i].toObject()["r"].toInt();
        uint8_t g = ledData[i].toObject()["g"].toInt();
        uint8_t b = ledData[i].toObject()["b"].toInt();

        QColor c = QColor(r,g,b);
        this->items[i]->setBrush(c);
    }
    setTime( data["time"].toInt() );
}
