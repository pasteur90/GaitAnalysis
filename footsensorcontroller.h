#ifndef FOOTSENSORCONTROLLER_H
#define FOOTSENSORCONTROLLER_H

#include "sensorcontroller.h"

#include <QObject>

class FootSensorController : public SensorController
{
    Q_OBJECT
public:
    explicit FootSensorController(const QBluetoothDeviceInfo info, QObject *parent = 0);
private slots:
    void updateSensorValue(const QLowEnergyCharacteristic &,
                           const QByteArray &);

};

#endif // FOOTSENSORCONTROLLER_H
