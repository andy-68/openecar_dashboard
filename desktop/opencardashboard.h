#ifndef OPENCARDASHBOARD_H
#define OPENCARDASHBOARD_H

#include <QMainWindow>
#include <QTimer>
#include "config.h"

#include "canproto.h"

namespace Ui {
class OpencarDashboard;
}

class OpencarDashboard : public QMainWindow
{
    Q_OBJECT

public:
    OpencarDashboard(QWidget *parent,config*);
    ~OpencarDashboard();

protected:
    virtual void resizeEvent(QResizeEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);

private slots:
    void deviceConnected();
    void deviceDisconnected();
    void refreshScreen();
    void FSOn();



private:
    Ui::OpencarDashboard*	ui;
    CanProto*				can	= NULL;
    QTimer*					tick = NULL;
    QTimer*					tFSO = NULL;
    bool					CANisOK = false;

//    QPixmap 				bkgnd;
};

#endif // OPENCARDASHBOARD_H
