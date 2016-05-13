#ifndef SENSORDATACOLLECTOR_H
#define SENSORDATACOLLECTOR_H

#include "sensorcontroller.h"

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QList>
#include <QString>

class SensorDataCollector : public QObject
{
    Q_OBJECT
private:
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QBluetoothDeviceInfo *m_leftFoot;
    QBluetoothDeviceInfo *m_rightFoot;
    QBluetoothDeviceInfo *m_accelerometer;
    SensorController *m_leftFootController;
    SensorController *m_rightFootController;
    SensorController *m_accelerometerController;

public:
    explicit SensorDataCollector(QObject *parent = 0);

signals:

public slots:
    void deviceSearch();
private slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);
    void scanFinished();
};

#endif // SENSORDATACOLLECTOR_H
