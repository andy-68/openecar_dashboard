#include "opencardashboard.h"
#include "ui_opencardashboard.h"

OpencarDashboard::OpencarDashboard(QWidget *parent,config* conf) :
    QMainWindow(parent),
    ui(new Ui::OpencarDashboard)
{
    ui->setupUi(this);

    can=new CanProto();
    connect(can,SIGNAL(deviceConnected()),this,SLOT(deviceConnected()));
    connect(can,SIGNAL(deviceDisconnected()),this,SLOT(deviceDisconnected()));
    can->useDevice(conf->getIfName());
    can->setDump(conf->getDumpOK());
    tick=new QTimer();
    tFSO=new QTimer();
    connect(tick,SIGNAL(timeout()),this,SLOT(refreshScreen()));
    connect(tFSO,SIGNAL(timeout()),this,SLOT(FSOn()));
    tick->setInterval(200);
    tFSO->setInterval(100);
    tFSO->setSingleShot(true);
    tick->start();
    if(conf->getFSM())tFSO->start();
    refreshScreen();
}

OpencarDashboard::~OpencarDashboard()
{
    delete can;
    delete ui;
}

void OpencarDashboard::resizeEvent(QResizeEvent *)
{
    this->setFixedHeight(this->width()*9/16);
//    QFont font=this->font();
    int fsize=this->size().width()/70;
    ui->label_OpenECAR->setFont(QFont("Aial",fsize,70));
    ui->label_Vdatetime->setFont(QFont("Aial",fsize,70));
    ui->label_Vodometer->setFont(QFont("Aial",fsize,70));
    ui->label_Vtemperature->setFont(QFont("Aial",fsize,70));

    fsize*=4;

    ui->label_VbatteryProc->setFont(QFont("Aial",fsize,70));
    ui->label_Vpower->setFont(QFont("Aial",fsize,70));
    ui->label_Vspeed->setFont(QFont("Aial",fsize,70));

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

void OpencarDashboard::FSOn()
{
    // It looks as set of crutches, but, if simply set FullScreen mode in constructor, it works
    // very strange (in Qt 5.7.0 and multy-monitor configuration)
    mouseDoubleClickEvent(NULL);
}

void OpencarDashboard::mouseDoubleClickEvent(QMouseEvent*)
{
    if(this->isFullScreen())this->setWindowState(this->windowState() &(!Qt::WindowFullScreen));
    else this->setWindowState(Qt::WindowFullScreen);
}
