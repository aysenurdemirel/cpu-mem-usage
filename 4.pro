TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        pidcpu.cpp \
        syscpu.cpp \
        sysmem.cpp

HEADERS += \
    pidcpu.h \
    syscpu.h \
    sysmem.h
