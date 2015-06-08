#ifndef SLIDERPARAMETER_H
#define SLIDERPARAMETER_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include "MainWindow.h"

class SliderParameter : public QWidget
{
    Q_OBJECT
public:
    SliderParameter(MainWindow *main, QString name, QString variable,
            float min, float max, float defaultValue, float gain=1,
            QWidget *parent = 0);

signals:

public slots:
    void updated();
    void reset();

protected:
    MainWindow *main;
    QVBoxLayout layout;
    QLabel label;
    QSlider slider;
    QString name, variable;
    float min, max, defaultValue, gain;

};

#endif // SLIDERPARAMETER_H
