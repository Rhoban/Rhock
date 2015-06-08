#include <iostream>
#include "Sequencer.h"
#include "MainWindow.h"

Sequencer::Sequencer(MainWindow *main_)
    : mainW(main_)
{
    divider = 0;
    timer.setInterval(200);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start();
}

Sequencer::~Sequencer()
{

}

void Sequencer::setValue(QString name, float value)
{
    mutex.lock();
    values[name] = value;
    mutex.unlock();
}

void Sequencer::tick()
{
    divider++;

    if (divider > 20) {
        divider = 0;
    } else {
        QString variable = "";
        float value;

        mutex.lock();
        if (values.size()) {
            auto item = values.begin();
            variable = item->first;
            value = item->second;
            values.erase(item);
        }
        mutex.unlock();

        if (variable != "") {
            mainW->setValue(variable, value);
        }
    }
}
