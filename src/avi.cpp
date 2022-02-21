#include "avi.h"

// TODO: QFile entfernen für raw C++!
#include <QFile>

AVI::AVI( uint8_t bytePerPixel, uint32_t width, uint32_t height ) :
    bytePerPixel(bytePerPixel), width(width), height(height)
{
}

void AVI::save()
{
    std::list<uint8_t> data;

    RIFFHeader riffHeader;
    riffHeader.signature[0] = 'R';
    riffHeader.signature[1] = 'I';
    riffHeader.signature[2] = 'F';
    riffHeader.signature[3] = 'F';
    riffHeader.size =
            sizeof(RIFFHeader) +
            sizeof(AVIHeader) + sizeof(AVIMainHeader) +
            sizeof(RIFFHeader) +
            sizeof(AVIHeader) + sizeof(AVIStreamHeader) +
            sizeof(AVIHeader) + sizeof(AVIStreamFormat) +
            10 * ( sizeof(RIFFHeader) + sizeof(SubChunk) );
    riffHeader.type[0] = 'A';
    riffHeader.type[1] = 'V';
    riffHeader.type[2] = 'I';
    riffHeader.type[3] = ' ';

    RIFFHeader hdrlList;
    hdrlList.signature[0] = 'L';
    hdrlList.signature[1] = 'I';
    hdrlList.signature[2] = 'S';
    hdrlList.signature[3] = 'T';
    hdrlList.size =
            sizeof(AVIHeader) + sizeof(AVIMainHeader) +
            sizeof(RIFFHeader) +
            sizeof(AVIHeader) + sizeof(AVIStreamHeader) +
            sizeof(AVIHeader) + sizeof(AVIStreamFormat);
    hdrlList.type[0] = 'h';
    hdrlList.type[1] = 'd';
    hdrlList.type[2] = 'r';
    hdrlList.type[3] = 'l';

    AVIHeader aviHeader;
    aviHeader.signature[0] = 'a';
    aviHeader.signature[1] = 'v';
    aviHeader.signature[2] = 'i';
    aviHeader.signature[3] = 'h';
    aviHeader.size = sizeof(AVIMainHeader);

    AVIMainHeader aviMainHeader;
    aviMainHeader.dwMicroSecPerFrame = 100000; // frame display rate (or 0)
    aviMainHeader.dwMaxBytesPerSec = 60000000; // max. transfer rate
    aviMainHeader.dwPaddingGranularity = 0; // pad to multiples of this size;
    aviMainHeader.dwFlags = 0; // the ever-present flags
    aviMainHeader.dwTotalFrames = 10; // # frames in file
    aviMainHeader.dwInitialFrames = 0;
    aviMainHeader.dwStreams = 1;
    aviMainHeader.dwSuggestedBufferSize = 60000000;
    aviMainHeader.dwWidth = 10;
    aviMainHeader.dwHeight = 1;
    aviMainHeader.dwReserved[0] = 0;
    aviMainHeader.dwReserved[1] = 0;
    aviMainHeader.dwReserved[2] = 0;
    aviMainHeader.dwReserved[3] = 0;

    RIFFHeader strlList;
    strlList.signature[0] = 'L';
    strlList.signature[1] = 'I';
    strlList.signature[2] = 'S';
    strlList.signature[3] = 'T';
    strlList.size =
            sizeof(AVIHeader) + sizeof(AVIStreamHeader) +
            sizeof(AVIHeader) + sizeof(AVIStreamFormat);
    strlList.type[0] = 's';
    strlList.type[1] = 't';
    strlList.type[2] = 'r';
    strlList.type[3] = 'l';

    AVIHeader strhHeader;
    strhHeader.signature[0] = 's';
    strhHeader.signature[1] = 't';
    strhHeader.signature[2] = 'r';
    strhHeader.signature[3] = 'h';
    strhHeader.size = sizeof(AVIStreamHeader);

    AVIStreamHeader aviStreamHeader;
    aviStreamHeader.fccType[0] = 'v';
    aviStreamHeader.fccType[1] = 'i';
    aviStreamHeader.fccType[2] = 'd';
    aviStreamHeader.fccType[3] = 's';
    aviStreamHeader.fccHandler[0] = 'r';
    aviStreamHeader.fccHandler[1] = 'a';
    aviStreamHeader.fccHandler[2] = 'w';
    aviStreamHeader.fccHandler[3] = ' ';
    aviStreamHeader.dwFlags = 0;
    aviStreamHeader.wPriority = 0;
    aviStreamHeader.wLanguage = 0 ;
    aviStreamHeader.dwInitialFrames = 0;
    aviStreamHeader.dwScale = 1;
    aviStreamHeader.dwRate = 10; /* dwRate / dwScale == samples/second */
    aviStreamHeader.dwStart = 0;
    aviStreamHeader.dwLength = 10; /* In units above... */
    aviStreamHeader.dwSuggestedBufferSize = 10000000;
    aviStreamHeader.dwQuality = 0;
    aviStreamHeader.dwSampleSize = 0;
    aviStreamHeader.rcFrame.left = 0;
    aviStreamHeader.rcFrame.top = 0;
    aviStreamHeader.rcFrame.right = 10;
    aviStreamHeader.rcFrame.bottom = 1;

    AVIHeader streamFormatHeader;
    streamFormatHeader.signature[0] = 's';
    streamFormatHeader.signature[1] = 't';
    streamFormatHeader.signature[2] = 'r';
    streamFormatHeader.signature[3] = 'f';
    streamFormatHeader.size = sizeof(AVIStreamFormat);

    AVIStreamFormat streamFormat;
    streamFormat.biSize = sizeof(AVIStreamFormat);
    streamFormat.biWidth = 10;
    streamFormat.biHeight = 1;
    streamFormat.biPlanes = 1;
    streamFormat.biBitCount = 24;
    streamFormat.biCompression = 0x0000;
    streamFormat.biSizeImage = 0;
    streamFormat.biXPelsPerMeter = 10;
    streamFormat.biYPelsPerMeter = 10;
    streamFormat.biClrUsed = 0;
    streamFormat.biClrImportant = 0;

    // Save data
    pushData(data, reinterpret_cast<uint8_t*>(&riffHeader), sizeof(riffHeader));
    pushData(data, reinterpret_cast<uint8_t*>(&hdrlList), sizeof(hdrlList));
    pushData(data, reinterpret_cast<uint8_t*>(&aviHeader), sizeof(aviHeader));
    pushData(data, reinterpret_cast<uint8_t*>(&aviMainHeader), sizeof(aviMainHeader));
    pushData(data, reinterpret_cast<uint8_t*>(&strlList), sizeof(strlList));
    pushData(data, reinterpret_cast<uint8_t*>(&strhHeader), sizeof(strhHeader));
    pushData(data, reinterpret_cast<uint8_t*>(&aviStreamHeader), sizeof(aviStreamHeader));
    pushData(data, reinterpret_cast<uint8_t*>(&streamFormatHeader), sizeof(streamFormatHeader));
    pushData(data, reinterpret_cast<uint8_t*>(&streamFormat), sizeof(streamFormat));

    for( int j = 0; j < 10; j++ )
    {
        RIFFHeader movi;
        movi.signature[0] = 'L';
        movi.signature[1] = 'I';
        movi.signature[2] = 'S';
        movi.signature[3] = 'T';
        movi.size = sizeof(SubChunk);
        movi.type[0] = 'm';
        movi.type[1] = 'o';
        movi.type[2] = 'v';
        movi.type[3] = 'i';

        SubChunk m1;
        m1.signature[0] = '0';
        m1.signature[1] = '0';
        m1.signature[2] = 'd';
        m1.signature[3] = 'b';
        m1.size = 30;

        for( int i = 0; i < 10; i++ )
        {
            m1.rgb[i].red = i*25;
            m1.rgb[i].green = j*25;
            m1.rgb[i].blue = 0;
        }

        pushData(data, reinterpret_cast<uint8_t*>(&movi), sizeof(movi));
        pushData(data, reinterpret_cast<uint8_t*>(&m1), sizeof(m1));
    }

    //////////////////////////////////////////
    ///         Should be removed           //
    //////////////////////////////////////////
    QFile f("test.avi");
    if(!f.open(QIODevice::WriteOnly))
    {
        qFatal("Can not open test.avi!");
        return;
    }
    for(auto d : data)
    {
        f.write(reinterpret_cast<char*>(&d), 1);
    }
    f.close();
}

uint32_t AVI::getPixelPerFrame()
{
    return width * height * bytePerPixel;
}

void AVI::pushData(std::list<uint8_t>& list, uint8_t *data, uint32_t size)
{
    while( size-- )
    {
        list.push_back(*data);
        data++;
    }
}

AVISubChunk::AVISubChunk(uint32_t frameSize)
{
    rgb = new RGB[frameSize];
}
