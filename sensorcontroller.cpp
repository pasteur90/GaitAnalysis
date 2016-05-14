#include "sensorcontroller.h"

#include <QDebug>

#define SERVICE_UUID 0x2220
#define CHAR_UUID 0x2221

SensorController::SensorController(const QBluetoothDeviceInfo info, QObject *parent) : QObject(parent),
    m_controller(new QLowEnergyController(info, this)),
    foundService(false),
    m_service(0),
    m_info(new QBluetoothDeviceInfo(info))
{

}

void SensorController::connectToDevice()
{

    qDebug() << "attempt to connect";
    connect(m_controller, SIGNAL(serviceDiscovered(QBluetoothUuid)),
            this, SLOT(serviceDiscovered(QBluetoothUuid)));
    connect(m_controller, SIGNAL(discoveryFinished()),
            this, SLOT(serviceScanDone()));
    connect(m_controller, SIGNAL(error(QLowEnergyController::Error)),
            this, SLOT(controllerError(QLowEnergyController::Error)));
    connect(m_controller, SIGNAL(connected()),
            this, SLOT(deviceConnected()));
    connect(m_controller, SIGNAL(disconnected()),
            this, SLOT(deviceDisconnected()));

    m_controller->setRemoteAddressType(QLowEnergyController::RandomAddress);
    m_controller->connectToDevice();
}

void SensorController::deviceConnected()
{
    qDebug() << "connected";
    m_controller->discoverServices();
}

void SensorController::deviceDisconnected()
{
    qWarning() << "Remote device disconnected";
}

void SensorController::serviceDiscovered(const QBluetoothUuid &gatt)
{
    qDebug() << "service Discovered";
    if (gatt == QBluetoothUuid(static_cast<quint16>(SERVICE_UUID))) {
        foundService = true;
    }
}

void SensorController::serviceScanDone()
{
    delete m_service;
    m_service = 0;

    if (foundService) {
        m_service = m_controller->createServiceObject(
                    QBluetoothUuid(static_cast<quint16>(SERVICE_UUID)), this);
    }

    if (!m_service) {
        return;
    }

    connect(m_service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
            this, SLOT(serviceStateChanged(QLowEnergyService::ServiceState)));
    connect(m_service, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
            this, SLOT(updateSensorValue(QLowEnergyCharacteristic,QByteArray)));
    connect(m_service, SIGNAL(descriptorWritten(QLowEnergyDescriptor,QByteArray)),
            this, SLOT(confirmedDescriptorWrite(QLowEnergyDescriptor,QByteArray)));

    //discover services; discovery process is indicated via the stateChanged() signal
    m_service->discoverDetails();
}

void SensorController::controllerError(QLowEnergyController::Error error)
{
    qWarning() << "Controller Error: " << error;
}

void SensorController::disconnectService()
{
    foundService = false;
    if (m_notificationDesc.isValid() && m_service) {
        m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0000"));
    }
    else {
        m_controller->disconnectFromDevice();
        delete m_service;
        m_service = 0;
    }
}

void SensorController::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    switch (s) {
    case QLowEnergyService::ServiceDiscovered:
    {
        const QLowEnergyCharacteristic chr = m_service->characteristic(
                    QBluetoothUuid(static_cast<quint16>(CHAR_UUID)));
        if (!chr.isValid()) {
            break;
        }

        const QLowEnergyDescriptor m_notificationDesc = chr.descriptor(
                    QBluetoothUuid::ClientCharacteristicConfiguration);
        if (m_notificationDesc.isValid()) {
            m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
            qDebug("measuring");
        }
        break;
    }
    default:
        //nothing for now
        break;
    }
}

void SensorController::serviceError(QLowEnergyService::ServiceError e)
{
    switch (e) {
    case QLowEnergyService::DescriptorWriteError:
//        setMessage("Cannot obtain notifications");
        break;
    default:
        qWarning() << "service error:" << e;
    }
}

//pure virtual function
//void SensorController::updateSensorValue(const QLowEnergyCharacteristic &c,
//                                         const QByteArray &value)
//{
//    qDebug() << value;
//}

void SensorController::confirmedDescriptorWrite(const QLowEnergyDescriptor &d,
                                                const QByteArray &value)
{
    if (d.isValid() && d == m_notificationDesc && value == QByteArray("0000")) {
        //disabled notifications -> assume disconnect intent
        m_controller->disconnectFromDevice();
        delete m_service;
        m_service = 0;
    }
}
