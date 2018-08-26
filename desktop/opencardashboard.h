#ifndef OPENCARDASHBOARD_H
#define OPENCARDASHBOARD_H

#include <QMainWindow>
#include <QTimer>

#include "canproto.h"

namespace Ui {
class OpencarDashboard;
}

class OpencarDashboard : public QMainWindow
{
    Q_OBJECT

public:
    OpencarDashboard(QWidget *parent,QString);
    ~OpencarDashboard();

virtual void resizeEvent(QResizeEvent*);

private slots:
    void deviceConnected();
    void deviceDisconnected();
    void refreshScreen();



private:
    Ui::OpencarDashboard*	ui;
    CanProto*				can	= NULL;
    QTimer*					tick = NULL;
    bool					CANisOK = false;
//    QPixmap 				bkgnd;
};

#endif // OPENCARDASHBOARD_H
