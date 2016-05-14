#include "footsensorcontroller.h"

FootSensorController::FootSensorController(const QBluetoothDeviceInfo info,
                                           QObject *parent)
    :SensorController(info, parent)
{

}

void FootSensorController::updateSensorValue(const QLowEnergyCharacteristic &, const QByteArray &)
{

}
