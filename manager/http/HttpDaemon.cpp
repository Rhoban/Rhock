#include <iostream>
#include <sstream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUrl>
#include <QStringList>
#include <QDateTime>
#include <json/json.h>
#include <MainWindow.h>
#include "HttpDaemon.h"

 HttpDaemon::HttpDaemon(quint16 port, MainWindow *main_, QObject* parent)
     : main(main_), QTcpServer(parent), disabled(false)
 {
     if (!listen(QHostAddress::Any, port)) {
         throw QString("Can't bind to port");
     }
 }

 void HttpDaemon::incomingConnection(qintptr socket)
 {
     if (disabled)
         return;

     // When a new client connects, the server constructs a QTcpSocket and all
     // communication with the client is done over this QTcpSocket. QTcpSocket
     // works asynchronously, this means that all the communication is done
     // in the two slots readClient() and discardClient().
     QTcpSocket* s = new QTcpSocket(this);
     connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
     connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
     s->setSocketDescriptor(socket);
 }

 void HttpDaemon::pause()
 {
     disabled = true;
 }

 void HttpDaemon::resume()
 {
     disabled = false;
 }

 void HttpDaemon::readClient()
 {
     if (disabled)
         return;

     // This slot is called when the client sent data to the server. The
     // server looks if it was a get request and sends a very simple HTML
     // document back.
     QTcpSocket* socket = (QTcpSocket*)sender();
     if (socket->canReadLine()) {
         QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
         if (tokens[0] == "GET" && tokens.size()>1) {
             QTextStream os(socket);
             os.setAutoDetectUnicode(true);
             handle(os, tokens[1]);
         }

         socket->close();
         if (socket->state() == QTcpSocket::UnconnectedState) {
             delete socket;
         }
     } else {
         std::cout << "Can't read line" << std::endl;
     }
 }

 void HttpDaemon::handle(QTextStream &stream, QString url)
 {
     QString data = "null";
     QString callback = "";
     if (url.mid(0, 2) == "/?") {
         data = url.mid(2);
         data = QUrl::fromPercentEncoding(data.toLatin1());
         QStringList parts = data.split("&");
         data = parts[0];
         for (int i=1; i<parts.size(); i++) {
             QString &part = parts[i];
             if (part.startsWith("callback=")) {
                 callback = part.mid(9);
             }
         }
     }

     Json::Reader reader;
     Json::Value request;
     Json::Value response(Json::arrayValue);

     if (reader.parse(data.toStdString(), request)) {
         if (request.isArray() && request.size()<=2 && request[0].isString()) {
             try {
                 response[0] = 1;
                 Json::Value null;
                 process(request[0].asString(), request.size()==2 ? request[1] : null, response[1]);
             } catch (std::string error) {
                 response[0] = 0;
                 response[1] = error;
             }
         } else {
             response[0] = 0;
             response[1] = "Bad request";
         }
     } else {
         response[0] = 0;
         response[1] = "Unable to parse the request";
     }

     Json::FastWriter writer;
     std::stringstream ss;
     if (callback != "") {
         ss << callback.toStdString() << "(";
     }
     ss << writer.write(response);
     if (callback != "") {
         ss << ");";
     }
     std::string responseData = ss.str();
     stream << "HTTP/1.0 200 Ok\r\n"
         "Content-Type: application/json; charset=\"utf-8\"\r\n" <<
         "Content-length: " << responseData.length() << "\r\n"
         "\r\n";
     stream << QString::fromStdString(responseData);
 }

 void HttpDaemon::process(std::string request, Json::Value &parameters, Json::Value &response)
 {
     if (request == "version") {
         response = "1.0";
     } else if (request == "command") {
         if (!parameters.isString()) {
             throw std::string("Command should be a string");
         }
         std::string command = parameters.asString()+"\r\n";

         if (!main->isConnected()) {
             throw std::string("Port is closed");
         }

         if (main->sendData(QString::fromStdString(command))) {
             response = main->getResponse().toStdString();
         } else {
             main->closeConnection();
             response = false;
         }
     } else if (request == "rhock") {
         response = Json::Value(Json::objectValue);
         response["version"] = "1.0";
         if (main->isConnected()) {
             main->sendData("rhock\r\nrhock\r\nrhock\r\n");
             response["rhock_ready"] = true;
         } else {
             response["rhock_ready"] = false;
         }
     } else if (request == "get") {
         main->checkConnection();
         if (!main->isConnected()) {
             throw std::string("Not connected");
         }
         response = Json::Value(Json::arrayValue);
         auto data = main->getData();
         if (data.length())
         std::cout << "<< ";
         for (int k=0; k<data.length(); k++) {
             std::cout << (int)(unsigned char)data.at(k) << " ";
             response[k] = (unsigned char)data.at(k);
         }
         std::cout << std::endl;
     } else if (request == "send") {
         if (main->isConnected() && parameters.isArray()) {
             QString buffer;
             std::cout << ">> ";
             for (int k=0; k<parameters.size(); k++) {
                 if (parameters[k].isInt()) {
                     std::cout << (int)(unsigned char)(parameters[k].asInt()) << " ";
                     buffer += (char)(parameters[k].asInt());
                 }
             }
             std::cout << std::endl;
             main->sendData(buffer);
             response = true;
         } else {
             response = false;
         }
     } else if (request == "connected") {
         response = main->isConnected();
     } else {
         throw std::string("Unknown request");
     }
 }

 void HttpDaemon::discardClient()
 {
     QTcpSocket* socket = (QTcpSocket*)sender();
     socket->deleteLater();
 }
