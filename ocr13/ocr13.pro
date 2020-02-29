#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T07:06:41
#
#-------------------------------------------------

QT       -= core
QT       -= gui

TARGET = gtkmm
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

#at
INCLUDEPATH += ../atlib

#openCV
INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
LIBS += `pkg-config opencv4 --libs`

#ocr
INCLUDEPATH += /usr/include/tesseract
INCLUDEPATH += /usr/include/leptonica
LIBS += -ltesseract -llept

#plot

SOURCES += \
    ../atlib/atOCR.cpp \
    ../atlib/at_File.cpp \
    ../atlib/at_Konfiguracja.cpp \
    atOCR_Garb.cpp \
    atOCR_Pik.cpp \
    atOCR_Pole.cpp \
    atOCR_Vertical.cpp \
    atOCR_Wiersz.cpp \
    main.cpp \
    mainwindow.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += gtkmm-3.0

HEADERS += \
    ../atlib/atErrors.h \
    ../atlib/atOCR.h \
    ../atlib/at_File.h \
    ../atlib/at_Konfiguracja.h \
    atOCR_Garb.h \
    atOCR_Pik.h \
    atOCR_Pole.h \
    atOCR_Vertical.h \
    atOCR_Wiersz.h \
    mainwindow.h
