#ifndef FIRMWAREUPLOADER_H
#define FIRMWAREUPLOADER_H

#include <QThread>

class MainWindow;
class FirmwareUploader : public QThread
{
    Q_OBJECT

    void run();

public:
    FirmwareUploader(MainWindow *main);
    void setPort(QString port);
    void setData(QByteArray data);

signals:
    void finished();
    void update(float alpha);
    void status(QString message);

protected:
    bool isReady(const QString &data);
    bool isSuccess(const QString &data);

    MainWindow *mainW;
    QString port;
    QByteArray data;
};

#endif // FIRMWAREUPLOADER_H
