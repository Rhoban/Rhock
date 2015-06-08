#include <iostream>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include <QMessageBox>
#include <QTime>
#include <QThread>
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sequencer(this),
    firmwareUploader(this)
{
    ui->setupUi(this);
    setWindowTitle(tr("Robot manager"));

    // Populate the ports list
    populatePorts();

    try {
        http = new HttpDaemon(5757, this);
    } catch (QString error) {
        QMessageBox::warning(this, tr("Error"), tr("Unable to run the manager, maybe it is already running?"));
        exit(EXIT_FAILURE);
    }

    QObject::connect(&port, SIGNAL(aboutToClose()), this, SLOT(on_port_close()));

    QObject::connect(ui->walkButton, SIGNAL(clicked()), this, SLOT(updateGait()));
    QObject::connect(ui->trotButton, SIGNAL(clicked()), this, SLOT(updateGait()));

    addParameter(new SliderParameter(this, tr("Freq."), "freq", 0.5, 3.0, 2.0, 10));
    addParameter(new SliderParameter(this, tr("Crab"), "crab", 0.0, 40.0, 0.0, 1));
    addParameter(new SliderParameter(this, tr("Height."), "h", -130, -30.0, -55.0, 1));
    addParameter(new SliderParameter(this, tr("Radius"), "r", 50, 130.0, 90.0, 1));
    addParameter(new SliderParameter(this, tr("Alt"), "alt", 0.0, 50.0, 20.0, 1));
    addParameter(new SliderParameter(this, tr("Pitch"), "frontH", -50.0, 50.0, 0.0, 0.5));

    QObject::connect(&versionDownloader, SIGNAL(downloaded(QByteArray)), this, SLOT(dowloadedVersion(QByteArray)));
    QObject::connect(&firmwareDownloader, SIGNAL(downloaded(QByteArray)), this, SLOT(dowloadedFirmware(QByteArray)));

    QObject::connect(&firmwareUploader, SIGNAL(finished()), this, SLOT(on_firmwareUploaded()));
    QObject::connect(&firmwareUploader, SIGNAL(update(float)), this, SLOT(on_firmwareUploadStep(float)));
    QObject::connect(&firmwareUploader, SIGNAL(status(QString)), this, SLOT(on_firmwareStatusChange(QString)));
    ui->progressBar->hide();

    setEnable(false);

    ui->reconnect->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToConnected()
{
    sendData(" \n");
    ui->disconnect->setEnabled(true);
    ui->ports->setEnabled(false);
    ui->refresh->setEnabled(false);
    ui->connect->hide();
    ui->reconnect->show();
    setMessage(tr("Connected"));
    setEnable(true);
}

void MainWindow::goToDisconnected()
{
    ui->ports->setEnabled(true);
    ui->disconnect->setEnabled(false);
    ui->refresh->setEnabled(true);
    ui->reconnect->hide();
    ui->connect->show();
    setMessage(tr("Disconnected"), true);
    setEnable(false);
}

void MainWindow::populatePorts()
{
    bluetooth.listDevices();
    ui->ports->clear();
    ui->firmwarePorts->clear();

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i=0; i<ports.size(); i++) {
        if (!ports[i].portName.startsWith("ttyS")) {
            QString description = ports[i].portName;
#ifdef WIN32
            if (ports[i].bluetoothAddr!="" && bluetooth.hasDevice(ports[i].bluetoothAddr)) {
                description = "Robot "+bluetooth.getDeviceName(ports[i].bluetoothAddr)+" ("+description+")";
            }
#endif
            ui->ports->addItem(description, ports[i].portName);
            ui->firmwarePorts->addItem(description, ports[i].portName);
        }
    }
}

void MainWindow::setMessage(QString message, bool error)
{
    QString text = "<font color=\"";
    if (error) text += "red";
    else text += "blue";
    text += "\">" + message + "</font>";
    ui->status->setText(text);
}

void MainWindow::checkConnection()
{
    bool portFound = false;

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i=0; i<ports.size(); i++) {
        if (ports[i].portName == currentPort) {
            portFound = true;
        }
    }

    if (!portFound || !port.isOpen()) {
        goToDisconnected();
        populatePorts();
    }
}

void MainWindow::closeConnection()
{
    if (port.isOpen()) {
        port.close();
        goToDisconnected();
    }
}

bool MainWindow::isConnected()
{
    return port.isOpen();
}

bool MainWindow::sendData(QString data)
{
    if (port.isOpen()) {
        int n = 0;
        do {
            n = port.readAll().length();
        } while (n > 0);

        port.write(data.toLatin1(), data.length());
        return port.isOpen();
    }
}

QByteArray MainWindow::getData()
{
    return port.readAll();
}

QString MainWindow::getResponse()
{
    QString response = "";
    QTime t;
    bool over = false;
    t.start();

    while (port.isOpen() && !over && t.elapsed()<500) {
        auto data = port.readAll();
        for (int i=0; i<data.length(); i++) {
            if (data[i] == '$') {
                over = true;
                break;
            } else {
                response += data[i];
            }
        }
        if (data.length()) {
            t.restart();
        }
        QThread::msleep(5);
    }

    return QStringList(response.split("\n").mid(1)).join("\n");
}

void MainWindow::on_refresh_clicked()
{
    populatePorts();
}

void MainWindow::on_connect_clicked()
{
    if (port.isOpen()) {
        port.close();
    }
    QString portName = ui->ports->itemData(ui->ports->currentIndex()).toString();
    currentPort = portName;

    port.setPortName(portName);
    if (port.open(QIODevice::ReadWrite)) {
        goToConnected();
    } else {
        ui->status->setText("<font color=\"red\">"+port.errorString()+"</font>");
    }
}

void MainWindow::on_port_close()
{
    goToDisconnected();
}

void MainWindow::on_disconnect_clicked()
{
    if (port.isOpen()) {
        port.close();
    }
}

void MainWindow::on_reconnect_clicked()
{
    on_connect_clicked();
}

void MainWindow::on_actionQuitter_triggered()
{
    if (port.isOpen()) {
        port.close();
    }
    close();
}

void MainWindow::on_startButton_clicked()
{
    updateAll();
    sendCommand("start\n");
    sequencer.setValue("dx", 0);
    sequencer.setValue("dy", 0);
    sequencer.setValue("turn", 0);
}

void MainWindow::on_stopButton_clicked()
{
    sendCommand("stop\n");
    sequencer.setValue("dx", 0);
    sequencer.setValue("dy", 0);
    sequencer.setValue("turn", 0);
}

void MainWindow::on_dxSlider_sliderMoved(int position)
{
    sequencer.setValue("dx", ui->dxSlider->value());
}

void MainWindow::on_dxSlider_sliderReleased()
{
    ui->dxSlider->setValue(0);
    sequencer.setValue("dx", 0);
}

void MainWindow::on_dySlider_sliderMoved(int position)
{
    sequencer.setValue("dy", ui->dySlider->value());
}

QString MainWindow::sendCommand(QString command, bool waitAnswer)
{
    sendData(command);
    if (waitAnswer) {
        return getResponse();
    } else {
        return "";
    }
}

void MainWindow::setValue(QString name, float value)
{
    QString data = QString("%1 %2\n").arg(name).arg(value);
    sendCommand(data);
}

bool MainWindow::getValue(QString name, float &output)
{
    if (port.isOpen()) {
        sendCommand(name+"\n");
        auto response = getResponse();
        QStringList parts = response.split("=");
        if (parts.size() >= 2) {
            output = parts[1].toFloat();
            return true;
        }
    }

    return false;
}

void MainWindow::setEnable(bool enabled)
{
    return;
    ui->tabWidget->setTabEnabled(1, enabled);
    ui->tabWidget->setTabEnabled(2, !enabled);
}

void MainWindow::addParameter(SliderParameter *parameter)
{
    parameters.push_back(parameter);
    ui->parameters->addWidget(parameter);
}

void MainWindow::updateAll()
{
    for (auto parameter : parameters) {
        parameter->updated();
    }

    updateGait();
}

void MainWindow::updateGait()
{
    if (ui->walkButton->isChecked()) gait = 0;
    if (ui->trotButton->isChecked()) gait = 1;
    sequencer.setValue("gait", gait);
}

void MainWindow::on_dySlider_sliderReleased()
{
    ui->dySlider->setValue(0);
    sequencer.setValue("dy", 0);
}

void MainWindow::on_turnSlider_sliderMoved(int position)
{
    sequencer.setValue("turn", ui->turnSlider->value());
}

void MainWindow::on_turnSlider_sliderReleased()
{
    ui->turnSlider->setValue(0);
    sequencer.setValue("turn", 0);
}

void MainWindow::on_resetButton_clicked()
{
    ui->walkButton->setChecked(false);
    ui->trotButton->setChecked(true);

    for (auto parameter : parameters) {
        parameter->reset();
    }
}

void MainWindow::on_checkVersion_clicked()
{
    versionDownloader.download("http://metabot.cc/files/firmware/metabot.version");
    ui->version->setText(tr("Obtaining the firmware..."));
}

void MainWindow::dowloadedVersion(const QByteArray &data)
{
    version = data.trimmed();
    ui->version->setText(tr("Getting firmware..."));
    firmwareDownloader.download("http://metabot.cc/files/firmware/metabot.bin");
}

void MainWindow::dowloadedFirmware(const QByteArray &data)
{
    firmware = data;
    ui->version->setText(QString(tr("Version %1, size: %2 bytes"))
                         .arg(version).arg(firmware.size()));
    ui->updateFirmware->setEnabled(true);
    ui->firmwarePorts->setEnabled(true);
    ui->updateFimwarePorts->setEnabled(true);
}

void MainWindow::on_updateFimwarePorts_clicked()
{
    populatePorts();
}

void MainWindow::on_updateFirmware_clicked()
{
    QString port = ui->firmwarePorts->itemData(ui->firmwarePorts->currentIndex()).toString();
    firmwareUploader.setPort(port);
    firmwareUploader.setData(firmware);
    firmwareUploader.start();

    ui->progressBar->show();
    ui->updateFirmware->setEnabled(false);
    ui->firmwarePorts->setEnabled(false);
    ui->updateFimwarePorts->setEnabled(false);
}

void MainWindow::on_firmwareUploadStep(float alpha)
{
    ui->progressBar->setValue(alpha*100);
}

void MainWindow::on_firmwareStatusChange(QString status)
{
    ui->firmwareStatus->setText(status);
}

void MainWindow::on_firmwareUploaded()
{
    ui->updateFirmware->setEnabled(true);
    ui->firmwarePorts->setEnabled(true);
    ui->updateFimwarePorts->setEnabled(true);
}
