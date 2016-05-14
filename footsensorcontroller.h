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
signals:
    void frontValue(const int);
    void backValue(const int);
};

#endif // FOOTSENSORCONTROLLER_H
