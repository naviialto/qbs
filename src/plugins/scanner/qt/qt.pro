DESTDIR= ../../../../plugins
TEMPLATE = lib
TARGET = qbs_qt_scanner

Qt = core xml

CONFIG += depend_includepath
unix: CONFIG += plugin

HEADERS += ../scanner.h
SOURCES += qt.cpp
