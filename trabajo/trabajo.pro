TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        estacionservicio.cpp \
        main.cpp \
        redestaciones.cpp \
        surtidor.cpp \
        tanque.cpp \
        transaccion.cpp

HEADERS += \
    estacionservicio.h \
    redestaciones.h \
    surtidor.h \
    tanque.h \
    transaccion.h
