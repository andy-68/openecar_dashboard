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
    void	setIfName(QString s){ifName=s;}
    void	setDumpOK(bool d)	{dumpOK=d;}

private:
    QString	ifName;
    bool	dumpOK	= false;
};

#endif // CONFIG_H
