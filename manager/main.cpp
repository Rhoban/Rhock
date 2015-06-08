#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("messages");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
