#ifndef VIDEO_H
#define VIDEO_H

#include <QList>
#include "frame.h"

class Video
{
public:
    Video();

    void addFrame(Frame* frame);
    void setLEDCount(int count);

    void render();
    void save(QString filename);

private:
    QList<Frame*> frames;
    int ledCount;
};

#endif // VIDEO_H
