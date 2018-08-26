#include "canproto.h"

CanProto::CanProto(QObject *parent) : QObject(parent)
{
    qDebug()<<"CanProto started!";
}

CanProto::~CanProto()
{
    qDebug()<<"CanProto finished!";
    if(canDevice)
    {
        canDevice->disconnectDevice();
        emit(deviceDisconnected());
        delete(canDevice);
    }
}

int CanProto::useDevice(QString deviceName)
{
    qDebug()<<"Try to use: "<<deviceName;
    canDevice = QCanBus::instance()->createDevice("socketcan", deviceName);
    if(!canDevice)
    {
        qDebug()<<"Can't use device '"<<deviceName<<"' via socketcan";
        return(0);
    }

    if(!canDevice->connectDevice())
    {
        qDebug()<<"Can't connect to device '"<<deviceName<<"'";
        delete(canDevice);
        emit(deviceError());
        emit(deviceDisconnected());
        return(0);
    }

    connect(canDevice, &QCanBusDevice::errorOccurred,this, &CanProto::procError);
    connect(canDevice, &QCanBusDevice::framesReceived,this, &CanProto::readFrames);
//    connect(canDevice, &QCanBusDevice::framesWritten,this, &CanProto::writeFrames);
    emit(deviceConnected());
    return(1);
}

static QByteArray dataToHex(const QByteArray &data)
{
    QByteArray result = data.toHex().toUpper();

    for (int i = 0; i < result.size(); i += 3)
        result.insert(i, ' ');

    return result;
}

void CanProto::readFrames()
{
    if(!canDevice)return;
    while(canDevice->framesAvailable())
    {
        QCanBusFrame frame=canDevice->readFrame();
        if (frame.frameType() != QCanBusFrame::ErrorFrame)
        {
            decodeFrame(frame);
        }
    }
}

void dumpFrame(const QCanBusFrame& frame)
{
    QString view;
    view += QLatin1String("Id: ");
    view += QString::number(frame.frameId(), 16).toUpper();
    view += QLatin1String(" bytes: ");
    view += QString::number(frame.payload().size(), 10);
    view += QLatin1String(" data: ");
    view += dataToHex(frame.payload());
    qDebug()<<view;
}


void CanProto::decodeFrame(const QCanBusFrame& frame)
{
        int		tmp;
        bool	changed	= true;

        switch (frame.frameId())
        {
            case 0x2d5:			// Battery charge level presize
                tmp=(quint8)frame.payload().at(4) & 0x03;
                tmp<<=8;
                tmp+=(quint8)frame.payload().at(5);
                batteryChargeLevelPresize=tmp/10.0;
                break;
            case 0x518:			// Battery charge level rounded
                batteryChargeLevelRounded=(quint8)frame.payload().at(7)/2.0;
                break;
            case 0x200:			// Speed, MPH
                tmp=(quint8)frame.payload().at(2);
                tmp<<=8;
                tmp+=(quint8)frame.payload().at(3);
                speedMPH=tmp/25.5;
                break;
            case 0x412:			// ODOmeter, miles
                tmp=(quint8)frame.payload().at(2);
                tmp<<=8;
                tmp+=(quint8)frame.payload().at(3);
                tmp<<=8;
                tmp+=(quint8)frame.payload().at(4);
                ODOmeter=(float)tmp;
                break;
            case 0x512:			// Time
                timestamp=QTime((quint8)frame.payload().at(0),(quint8)frame.payload().at(1));
                break;
            case 0x448:			// Hi Voltage
                tmp=(quint8)frame.payload().at(6);
                tmp<<=8;
                tmp+=(quint8)frame.payload().at(7);
                hiVolts=tmp/10.0;
                break;
            case 0x508:			// Hi Amps
                tmp=(quint8)frame.payload().at(2) & 0x3f;
                tmp<<=8;
                tmp+=(quint8)frame.payload().at(3);
                tmp-=0x2000;
                hiAmps=tmp/10.0;
                break;
            default:
                changed=false;
                dumpFrame(frame);
                break;
        }
        if(changed)emit(dataReceived());
}

/*
void CanProto::writeFrames()
{
    qDebug()<<"Frame sent!";
}
*/

void CanProto::procError()
{
    qDebug()<<"Error occured!";
    qDebug()<<canDevice->errorString();
    emit(deviceError());
}
