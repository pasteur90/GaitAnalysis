#ifndef ACCELEROMETERCONTROLLER_H
#define ACCELEROMETERCONTROLLER_H

#include "sensorcontroller.h"

#include <QObject>
#include <QFile>
#include <QTextStream>

class AccelerometerController : public SensorController
{
    Q_OBJECT
public:
    explicit AccelerometerController(const QBluetoothDeviceInfo info, QObject *parent = 0);
private slots:
    void updateSensorValue(const QLowEnergyCharacteristic &,
                           const QByteArray &);
signals:
    void xValue(const int);
    void yValue(const int);
    void zValue(const int);
private:
    QFile *m_file;
    QTextStream *m_stream;
};

#endif // ACCELEROMETERCONTROLLER_H
