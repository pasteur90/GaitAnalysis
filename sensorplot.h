#ifndef SENSORPLOT_H
#define SENSORPLOT_H

#include <QObject>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class SensorPlot : public QwtPlot
{
    Q_OBJECT
public:
    explicit SensorPlot(QWidget *parent = 0);
private:
    QwtPlotCurve *m_curve;
};

#endif // SENSORPLOT_H
