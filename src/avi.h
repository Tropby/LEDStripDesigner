#ifndef AVI_H
#define AVI_H

#include <stdint.h>
#include <list>

#pragma pack(1)

typedef struct __attribute__((packed, aligned(1)))
{
    uint8_t signature[4];
    uint32_t size;
    uint8_t type[4];
} RIFFHeader;

typedef struct __attribute__((packed, aligned(1)))
{
    uint8_t signature[4];
    uint32_t size;
} AVIHeader;

typedef struct __attribute__((packed, aligned(1)))
{
    uint32_t dwMicroSecPerFrame; // frame display rate (or 0)
    uint32_t dwMaxBytesPerSec; // max. transfer rate
    uint32_t dwPaddingGranularity; // pad to multiples of this
    // size;
    uint32_t dwFlags; // the ever-present flags
    uint32_t dwTotalFrames; // # frames in file
    uint32_t dwInitialFrames;
    uint32_t dwStreams;
    uint32_t dwSuggestedBufferSize;
    uint32_t dwWidth;
    uint32_t dwHeight;
    uint32_t dwReserved[4];
} AVIMainHeader;

typedef struct __attribute__((packed, aligned(1)))
{
    uint8_t fccType[4];
    uint8_t fccHandler[4];
    uint32_t dwFlags;
    uint16_t wPriority;
    uint16_t wLanguage;
    uint32_t dwInitialFrames;
    uint32_t dwScale;
    uint32_t dwRate; /* dwRate / dwScale == samples/second */
    uint32_t dwStart;
    uint32_t dwLength; /* In units above... */
    uint32_t dwSuggestedBufferSize;
    uint32_t dwQuality;
    uint32_t dwSampleSize;
    struct {
      int16_t left;
      int16_t top;
      int16_t right;
      int16_t bottom;
    } rcFrame;
} AVIStreamHeader;

typedef struct __attribute__((packed, aligned(1)))
{
  uint32_t biSize;
  int32_t  biWidth;
  int32_t  biHeight;
  uint16_t  biPlanes;
  uint16_t  biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t  biXPelsPerMeter;
  int32_t  biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
} AVIStreamFormat;


typedef struct __attribute__((packed, aligned(1)))
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB;

typedef struct __attribute__((packed, aligned(1)))
{
  uint8_t signature[4];
  uint32_t size;
  RGB rgb[10];
} SubChunk;

class AVISubChunk
{
public:
    AVISubChunk( uint32_t frameSize );

private:
    uint8_t signature[4];
    uint32_t size;
    RGB * rgb;
};

class AVI
{
public:
    AVI( uint8_t bytePerPixel, uint32_t width, uint32_t height );

    void setFrame( uint8_t * frameData );

    void save();

private:
    uint8_t bytePerPixel;
    uint32_t width;
    uint32_t height;

    std::list<AVISubChunk*> frames;

    uint32_t getPixelPerFrame();

    void pushData(std::list<uint8_t>& list, uint8_t* data, uint32_t size);
};

#endif // AVI_H
