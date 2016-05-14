#include "accelerometercontroller.h"

AccelerometerController::AccelerometerController(const QBluetoothDeviceInfo info,
                                                 QObject *parent)
    :SensorController(info, parent)
{

}

void AccelerometerController::updateSensorValue(const QLowEnergyCharacteristic &c,
                                                const QByteArray &value)
{
//    qDebug() << "accelerometer x: " << value.mid(0, 4).toInt()
//             << " y: " << value.mid(4, 4).toInt()
//             << " z: " << value.mid(8, 4).toInt();
    emit xValue(value.mid(0,4).toInt());
    emit yValue(value.mid(4,4).toInt());
    emit zValue(value.mid(8,4).toInt());
}
