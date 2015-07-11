#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include "interface/SIMFPGA.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
//    QGuiApplication app(argc, argv);

//    QtQuick2ApplicationViewer viewer;
//    viewer.setMainQmlFile(QStringLiteral("qml/SIMfishy/main.qml"));
//    viewer.showExpanded();

    int ret = 0;//app.exec();

    SIMFPGA* SimFPGA = new SIMFPGA();

    std::string in;

    std::cout<<"enter something to write to outfp\n";
    std::cout<<"enter b to break\n";
    while (1)
    {
        getline(std::cin,in);
        if (in == "b")
            break;
        else
            SimFPGA->write(in);
    }

    delete SimFPGA;
    return ret;
}
