TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cpumem_usage.cpp \
        main.cpp \
        pidcpu.cpp \
        pidmem.cpp \
        syscpu.cpp \
        sysmem.cpp

HEADERS += \
    cpumem_usage.h \
    pidcpu.h \
    pidmem.h \
    syscpu.h \
    sysmem.h
