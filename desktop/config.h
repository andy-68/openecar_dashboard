#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QString>

class config : public QObject
{
    Q_OBJECT
public:
    explicit config(QObject *parent = 0);

signals:

public slots:
    QString	getIfName()			{return(ifName);}
    bool	getDumpOK()			{return(dumpOK);}
    bool	getFSM()			{return(FSM);}
    void	setIfName(QString s){ifName=s;}
    void	setDumpOK(bool d)	{dumpOK=d;}
    void	setFSM(bool d)		{FSM=d;}

private:
    QString	ifName;
    bool	dumpOK	= false;
    bool	FSM		= false;
};

#endif // CONFIG_H
