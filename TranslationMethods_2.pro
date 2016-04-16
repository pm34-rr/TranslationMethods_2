TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Tables/ChangeableTable.cpp \
    Tables/Lexeme.cpp \
    Tables/PermamentTable.cpp

HEADERS += \
    Tables/ChangeableTable.h \
    Tables/Lexeme.h \
    Tables/PermamentTable.h

OBJECTS_DIR = objects
