#include "video.h"
#include <QFile>

Video::Video()
{

}

void Video::addFrame(Frame *frame)
{
    frames.append(frame);
}

void Video::setLEDCount(int count)
{
    ledCount = count;
}

void Video::render()
{
    for(auto f : frames )
    {        
        f->render();
    }
}

void Video::save(QString filename)
{
    QFile file;
    file.setFileName(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        for( Frame * frame : frames )
        {
            for( int i = 0; i < frame->getTime(); i++ )
            {
                uint8_t buffer[1024];
                uint16_t size = frame->getRawData(buffer, 1024);
                file.write((char*)buffer, size);
                while( size < 1024 )
                {
                    file.write("\xFF", 1);
                    size++;
                }
            }
        }
        file.close();
    }
    else
    {
        qFatal("Can not open file!");
    }
}
