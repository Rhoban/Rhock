#include <iostream>
#include "SliderParameter.h"

SliderParameter::SliderParameter(MainWindow *main_, QString name_, QString variable_,
                                 float min_, float max_, float defaultValue_, float gain_, QWidget *parent)
    : main(main_), name(name_), variable(variable_),
      min(min_), max(max_), defaultValue(defaultValue_), gain(gain_)
{
    setParent(main);
    label.setText("<b>"+name+"</b>");

    slider.setMinimum(min*gain);
    slider.setMaximum(max*gain);
    slider.setValue(defaultValue*gain);
    slider.setTickInterval(2);
    slider.setTickPosition(QSlider::TickPosition::TicksLeft);

    setLayout(&layout);
    layout.addWidget(&label);
    layout.addWidget(&slider);

    QObject::connect(&slider, SIGNAL(sliderMoved(int)), this, SLOT(updated()));
}

void SliderParameter::updated()
{
    float value = slider.value()/gain;
    main->sequencer.setValue(variable, value);
}

void SliderParameter::reset()
{
    slider.setValue(defaultValue*gain);
    updated();
}
