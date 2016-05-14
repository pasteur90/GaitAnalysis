#include "sensorplot.h"

SensorPlot::SensorPlot(QWidget *parent) : QwtPlot(parent),
    m_curve(new QwtPlotCurve())
{

}

