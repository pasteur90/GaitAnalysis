#include "accelerometercontroller.h"

AccelerometerController::AccelerometerController(const QBluetoothDeviceInfo info,
                                                 QObject *parent)
    :SensorController(info, parent)
{

}

void AccelerometerController::updateSensorValue(const QLowEnergyCharacteristic &, const QByteArray &)
{

}
