#include <iostream>
#include <QTime>
#include "FirmwareUploader.h"
#include "qextserialport.h"

FirmwareUploader::FirmwareUploader(MainWindow *main)
    : mainW(main)
{
}

void FirmwareUploader::setPort(QString port_)
{
    port = port_;
}

void FirmwareUploader::setData(QByteArray data_)
{
    data = data_;
}

bool FirmwareUploader::isReady(const QString &data)
{
    return data.contains("Ready") || data.contains("Rady") || data.contains("dy..");
}

bool FirmwareUploader::isSuccess(const QString &data)
{
    return data.contains("Success") || data.contains("ss..") || data.contains("Scc");
}

void FirmwareUploader::run()
{
    QTime t;
    QextSerialPort p(port);
    p.setPortName(port);

    emit update(0);
    emit status("Connecting to port...");

    if (p.open(QIODevice::ReadWrite)) {
        emit status("Connected, going to bootloader...");
        QThread::msleep(100);
        p.setRts(true);
        p.setDtr(false);
        QThread::msleep(100);
        p.setRts(false);
        p.write("CM9X");
        p.close();
        emit status("Rebooting the board...");
        QThread::msleep(1000);

        if (p.open(QIODevice::ReadWrite)) {
            QThread::msleep(100);
            emit status("Entering program mode...");
            p.write("AT&LD");
            QString received;
            t.start();

            while (!isReady(received) && t.elapsed()<5000) {
                received += p.readAll();
                QThread::msleep(100);
            }
            if (isReady(received)) {
                emit status("Ready! Sending firmware...");

                char *raw = data.data();
                unsigned int position = 0;
                unsigned int size = data.size();
                unsigned char checksum = 0;
                while (position < size) {
                    QByteArray tmp;
                    for (int k=0; (k<1024) && (position<size); k++) {
                        unsigned char c = raw[position++];
                        tmp += c;
                        checksum += c;
                    }

                    emit update(position/(float)size);
                    p.write(tmp);
                }
                p.setDtr(true);
                p.write((char*)&checksum, 1);
                emit status(QString("Firmware was sent."));

                received = "";
                t.start();
                while (!isSuccess(received) && t.elapsed()<5000) {
                    auto r = p.readAll();
                    if (r != "") std::cout << QString(r).toStdString() << std::endl;
                    received += r;
                    QThread::msleep(100);
                }
                if (isSuccess(received)) {
                    p.write("AT&RST");
                    emit status("Success. Running the code.");
                }
            }
        }
    } else {
        emit status(QString("Unable to open the port (%1)").arg(p.errorString()));
    }
    p.close();
    emit finished();
}
