#ifndef SENSORPLOT_H
#define SENSORPLOT_H

#include <QObject>
#include <qwt_plot.h>

class SensorPlot : public QwtPlot
{
    Q_OBJECT
public:
    explicit SensorPlot(QWidget *parent = 0);
};

#endif // SENSORPLOT_H
