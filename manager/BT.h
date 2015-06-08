#ifndef _BT
#define _BT

#include <QMap>
#include <QList>
#include <QString>

struct BTInfo
{
    QString address;
    QString name;
    bool connected;
};

class BT
{
public:
    BT();

    void listDevices();

    bool hasDevice(QString addr);
    QString getDeviceName(QString addr);

    QMap<QString, BTInfo> entries;
};

#endif // WINBT
