#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include <QLowEnergyController>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyService>
#include <QLowEnergyDescriptor>

class SensorController : public QObject
{
    Q_OBJECT
private:
    QLowEnergyController *m_controller;
    bool foundService;
    QLowEnergyService *m_service;
    QLowEnergyDescriptor m_notificationDesc;

public:
    explicit SensorController(const QBluetoothDeviceInfo info, QObject *parent = 0);

signals:

public slots:
    void disconnectService();
private slots:
    void deviceConnected();
    void deviceDisconnected();
    void serviceDiscovered(const QBluetoothUuid &);
    void serviceScanDone();
    void controllerError(QLowEnergyController::Error);
    void serviceStateChanged(QLowEnergyService::ServiceState);
    void serviceError(QLowEnergyService::ServiceError);
    void updateSensorValue(const QLowEnergyCharacteristic &,
                           const QByteArray &);
    void confirmedDescriptorWrite(const QLowEnergyDescriptor &,
                                  const QByteArray &);
};

#endif // SENSORCONTROLLER_H
