#include "opencardashboard.h"
#include "ui_opencardashboard.h"

OpencarDashboard::OpencarDashboard(QWidget *parent,QString device) :
    QMainWindow(parent),
    ui(new Ui::OpencarDashboard)
{
    ui->setupUi(this);

    can=new CanProto();
    connect(can,SIGNAL(deviceConnected()),this,SLOT(deviceConnected()));
    connect(can,SIGNAL(deviceDisconnected()),this,SLOT(deviceDisconnected()));
    can->useDevice(device);
    tick=new QTimer();
    connect(tick,SIGNAL(timeout()),this,SLOT(refreshScreen()));
    tick->setInterval(200);
    tick->start();
    refreshScreen();
}

OpencarDashboard::~OpencarDashboard()
{
    delete can;
    delete ui;
}

void OpencarDashboard::resizeEvent(QResizeEvent *)
{
    QPixmap bkgnd (":/pictures/openecar_dashboard_cln.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    palette.setColor(QPalette::WindowText, QColor::fromRgb(255,255,255));
    this->setPalette(palette);
}

void OpencarDashboard::deviceConnected()
{
    qDebug()<<"main: device connected!";
    CANisOK=true;
}

void OpencarDashboard::deviceDisconnected()
{
    qDebug()<<"main: device disconnected!";
    CANisOK=false;
}

void OpencarDashboard::refreshScreen()
{
    if(!CANisOK)return;
    if(!can)return;
    ui->label_Vdatetime->setText(can->getTimestamp().toString("h:m"));
    ui->label_Vtemperature->setText(QString().asprintf("%3.1f degC",can->getExtTemperature()));
    ui->label_Vspeed->setText(QString().asprintf("%2.0f",can->getSpeedImper()));
    ui->label_VbatteryProc->setText(QString().asprintf("%2.0f",can->getBatteryLevelRounded()));
    ui->label_Vodometer->setText(QString().asprintf("Odo: %10.0f km",can->getODOmeterMetric()));
    ui->label_Vpower->setText(QString().asprintf("%3.1f",can->getHiApms()*can->getHiVolage()/1000));
}
