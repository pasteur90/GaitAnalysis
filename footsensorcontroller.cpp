#include "footsensorcontroller.h"

FootSensorController::FootSensorController(const QBluetoothDeviceInfo info,
                                           QObject *parent)
    :SensorController(info, parent)
{

}

void FootSensorController::updateSensorValue(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    qDebug() << m_info->name()
                << " foot 1: " << value.mid(0, 4).toInt()
             << " foot 2: " << value.mid(4, 4).toInt();
}
