#include "footsensorcontroller.h"
#include <QDateTime>

FootSensorController::FootSensorController(const QBluetoothDeviceInfo info,
                                           QObject *parent)
    :SensorController(info, parent), m_file(0), m_stream(0)
{
    QString fileName = QString("/home/hci/data/") + QDateTime::currentDateTime().toString();
    if (info.name() == QString("HGinnoR")) {
        fileName += QString("Right.csv");
    }
    else {
        fileName += QString("Left.csv");
    }
    m_file = new QFile(fileName);
    if (m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_stream = new QTextStream(m_file);
    }
}

void FootSensorController::updateSensorValue(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
//    qDebug() << m_info->name()
//                << " foot 1: " << value.mid(0, 4).toInt()
//             << " foot 2: " << value.mid(4, 4).toInt();
    emit frontValue(value.mid(0, 4).toInt());
    emit backValue(value.mid(4, 4).toInt());

    (*m_stream) << QDateTime::currentMSecsSinceEpoch() << ", " << value.mid(0,4).toInt() << ", " << value.mid(4, 4).toInt() << "\n";
    m_stream->flush();
}
