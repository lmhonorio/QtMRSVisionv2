#-------------------------------------------------
#
# Project created by QtCreator 2016-11-18T20:21:47
#
#-------------------------------------------------

QT       += core gui



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMRSVision
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basegigecamera.cpp \
    flircamera.cpp \
    temperature.cpp \
    usbcam.cpp

HEADERS  += mainwindow.h \
    flircamera.hpp \
    temperature.hpp \
    basegigecamera.hpp \
    usbcam.hpp

FORMS    += \
    mainwindow.ui



#opencv
INCLUDEPATH += "C:\opencv24\opencv\build\install32\include"
LIBS += -L"C:\opencv24\opencv\build\install32\lib"
LIBS += -L"C:\opencv24\opencv\build\install32\bin"
LIBS += -lopencv_core2411d -lopencv_highgui2411d -lopencv_imgproc2411d -lopencv_legacy2411d
#LIBS += -lopencv_core2411 -lopencv_highgui2411 -lopencv_imgproc2411 -lopencv_legacy2411



#jai-gigbethernet
INCLUDEPATH += "C:\Program Files\JAI\SDK\library\CPP\include"
LIBS += -L"C:\Program Files\JAI\SDK\library\CPP\lib\Win32_i86"
LIBS += -lJai_Factory
