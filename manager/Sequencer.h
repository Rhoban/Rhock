#ifndef SEQUENCER_H
#define SEQUENCER_H
#include <QObject>
#include <QTimer>
#include <QMutex>

class MainWindow;

class Sequencer : public QObject
{
    Q_OBJECT

public:
    Sequencer(MainWindow *main);
    virtual ~Sequencer();

    void setValue(QString name, float value);

public slots:
    void tick();

protected:
    int divider;
    QMutex mutex;
    std::map<QString, float> values;
    QTimer timer;
    MainWindow *mainW;
};

#endif // SEQUENCER_H
