QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/avi.cpp \
    src/dialogcolors.cpp \
    src/dialoglog.cpp \
    src/frame.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/video.cpp

HEADERS += \
    src/avi.h \
    src/dialogcolors.h \
    src/dialoglog.h \
    src/frame.h \
    src/mainwindow.h \
    src/video.h

FORMS += \
    src/dialogcolors.ui \
    src/dialoglog.ui \
    src/mainwindow.ui

RESOURCES += \
    res.qrc
