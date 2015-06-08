#pragma once

#include <QTcpServer>
#include <json/json.h>

class MainWindow;
class HttpDaemon : public QTcpServer
 {
     Q_OBJECT

 public:
     HttpDaemon(quint16 port, MainWindow *serialPort, QObject* parent = 0);

     void incomingConnection(qintptr socket);

     void pause();
     void resume();

     void handle(QTextStream &stream, QString url);
     void process(std::string request, Json::Value &parameters, Json::Value &response);
private slots:
     void readClient();

     void discardClient();

 private:
     bool disabled;
     MainWindow *main;
 };
