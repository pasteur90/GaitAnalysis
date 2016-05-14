#ifndef ACCELEROMETERCONTROLLER_H
#define ACCELEROMETERCONTROLLER_H

#include "sensorcontroller.h"

#include <QObject>

class AccelerometerController : public SensorController
{
    Q_OBJECT
public:
    explicit AccelerometerController(const QBluetoothDeviceInfo info, QObject *parent = 0);
private slots:
    void updateSensorValue(const QLowEnergyCharacteristic &,
                           const QByteArray &);
};

#endif // ACCELEROMETERCONTROLLER_H
