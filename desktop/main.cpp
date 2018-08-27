#include "opencardashboard.h"
#include <QApplication>
#include <QCommandLineParser>
#include "config.h"

int main(int argc, char *argv[])
{
    QString	device;
    QCommandLineParser	csi;
    QApplication 		me(argc, argv);
    config 				conf;

    QCommandLineOption dev({{"d","device"},"interface to use for CAN-bus access","interface"});
    QCommandLineOption dmp({{"c","can_dump"},"dump all CAN messages"});
    QCommandLineOption fsm({{"f","fullscreen"},"start in full-screen mode"});

    csi.addHelpOption();
    csi.setApplicationDescription("Opencar Dashboard");
    csi.addOption(dev);
    csi.addOption(dmp);
    csi.addOption(fsm);
    csi.process(me);

    if(csi.isSet(dev))
    {
        conf.setIfName(csi.value(dev));
        if(!conf.getIfName().size())return(1);
        conf.setDumpOK(csi.isSet(dmp));
        conf.setFSM(csi.isSet(fsm));
        OpencarDashboard w(0,&conf);
        w.show();
        return me.exec();
    }
    return(0);
}
