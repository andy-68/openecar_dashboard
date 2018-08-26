#include "opencardashboard.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QString	device;
    QCommandLineParser	csi;
    QApplication me(argc, argv);

    QCommandLineOption dev({{"d","device"},"interface to use for CAN-bus access","interface"});

    csi.addHelpOption();
    csi.setApplicationDescription("Opencar Dashboard");
    csi.addOption(dev);
    csi.process(me);

    if(csi.isSet(dev))
    {
        device=csi.value(dev);
        if(!device.size())return(1);

        OpencarDashboard w(0,QString(device));
        w.show();
        return me.exec();
    }
    return(0);
}
