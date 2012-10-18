TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp
QMAKE_CXXFLAGS = -std=c++11 -pthread
LIBS += -pthread
