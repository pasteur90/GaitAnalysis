#include "accelerometercontroller.h"
#include <QDateTime>

AccelerometerController::AccelerometerController(const QBluetoothDeviceInfo info,
                                                 QObject *parent)
    :SensorController(info, parent), m_file(0), m_stream(0)
{
    m_file = new QFile(QString("/home/hci/data/") + QDateTime::currentDateTime().toString() + QString("acc.csv"));
    if (m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_stream = new QTextStream(m_file);
    }
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

    (*m_stream) << QDateTime::currentMSecsSinceEpoch() << ", " << value.mid(0,4).toInt() << ", " << value.mid(4,4).toInt() << ", " << value.mid(8,4).toInt() << "\n";
    m_stream->flush();
}
