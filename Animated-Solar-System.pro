QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += -L/usr/local/lib -lGLU -lglut -lGLEW
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    planet.cpp \
    satillite.cpp \
    solarsystem.cpp \
    viewwidget.cpp

HEADERS += \
    mainwindow.h \
    planet.h \
    satillite.h \
    solarsystem.h \
    stb_image.h \
    viewwidget.h

copydata.commands = $(COPY_DIR) $$PWD/textures $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
