#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <QGraphicsRectItem>
#include <QJsonObject>
#include <QJsonArray>

#pragma pack(push,1)

class Frame
{
public:
    Frame(int ledCount);
    void render();
    uint16_t getLEDCount();
    uint16_t getRawData(uint8_t *data, uint16_t maxSize);
    QGraphicsRectItem *getGraphicsItem(int index);
    QGraphicsTextItem *getShowTime();
    void setTime(int timeInFrames);
    int getTime();

    QJsonObject save();
    void load(QJsonObject data);
    void showLedCount(int count);

private:
    QGraphicsRectItem** items;
    QGraphicsTextItem* showTime;
    int time;

    uint16_t ledCount;

    typedef struct __attribute__((packed)) {
        uint8_t g;
        uint8_t r;
        uint8_t b;
    } LED;

    LED* data;
};

#pragma pack(pop)


#endif // FRAME_H

