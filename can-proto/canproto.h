#ifndef CANPROTO_H
#define CANPROTO_H

#include <QObject>
#include <QCanBusFrame>
#include <QCanBus>
#include <QString>
#include <QByteArray>
#include <QTime>

#include <QDebug>

class CanProto : public QObject
{
    Q_OBJECT
public:
    explicit CanProto(QObject *parent = 0);
            ~CanProto();

    int		useDevice(QString);
    void	decodeFrame(const QCanBusFrame&);

signals:
    void deviceConnected();
    void deviceDisconnected();
    void deviceError();
    void dataReceived();

public slots:
    float	getBatteryLevelPresise(){return(batteryChargeLevelPresize);}
    float	getBatteryLevelRounded(){return(batteryChargeLevelRounded);}
    float	getSpeedMetric()		{return(speedMPH*1.60934);}
    float	getSpeedImper()			{return(speedMPH);}
    float	getODOmeterMetric()		{return(ODOmeter);}
    float	getODOmeterImper()		{return(ODOmeter/1.60934);}
    float	getHiApms()				{return(hiAmps);}
    float	getHiVolage()			{return(hiVolts);}
    float	getExtTemperature()		{return(extTemperature);}
    QTime	getTimestamp()			{return(timestamp);}
    void	setDump(bool d)			{dumpOK=d;}

private slots:
    void readFrames();
//    void writeFrame();
    void procError();

private:
    QCanBusDevice*	canDevice = NULL;

    float 	batteryChargeLevelPresize	= 0;
    float 	batteryChargeLevelRounded	= 0;
    float	speedMPH					= 0;
    float	ODOmeter					= 0;
    float	hiAmps						= 0;
    float	hiVolts						= 0;
    float	extTemperature				= 0;
    QTime	timestamp					= QTime(0,0);
    bool	dumpOK						= false;
};

#endif // CANPROTO_H
