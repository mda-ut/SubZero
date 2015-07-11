# Add more folders to ship with the application, here
folder_01.source = qml/SIMfishy
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

#Include c++ 11
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

TEMPLATE = app
TARGET = SIMfishy

#Libraries
LIBS += -L/usr/local/lib \

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/interface/SIMInterface.cpp \
    src/interface/SIMFPGA.cpp \
    src/util/Logger.cpp \
    src/util/PropertyReader.cpp \
    src/util/Timer.cpp \
    src/util/Util.cpp \
    src/world/entities/Submarine.cpp \
    src/world/entities/Motor.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    src/interface/SIMFPGA.h \
    src/interface/SIMInterface.h \
    src/util/Logger.h \
    src/util/PropertyReader.h \
    src/util/Timer.h \
    src/util/Util.h \
    src/world/entities/Submarine.h \
    src/world/entities/Motor.h
