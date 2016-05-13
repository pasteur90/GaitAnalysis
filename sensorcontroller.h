#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>

class SensorController : public QObject
{
    Q_OBJECT
public:
    explicit SensorController(QObject *parent = 0);

signals:

public slots:
};

#endif // SENSORCONTROLLER_H
