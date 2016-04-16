TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Tables/ChangeableTable.cpp \
    Tables/Lexeme.cpp \
    Tables/PermamentTable.cpp \
    LexicalAnalyzer.cpp \
    TableStorage.cpp \
    Translator.cpp \
    Token.cpp

HEADERS += \
    Tables/ChangeableTable.h \
    Tables/Lexeme.h \
    Tables/PermamentTable.h \
    LexicalAnalyzer.h \
    TableStorage.h \
    Translator.h \
    Token.h

OBJECTS_DIR = objects
