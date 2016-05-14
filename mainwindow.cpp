#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensordatacollector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_deviceDiscoveryAgent(0),
    m_leftFoot(0), m_rightFoot(0), m_accelerometer(0),
    m_leftFootController(0), m_rightFootController(0), m_accelerometerController(0)
{
    ui->setupUi(this);
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(m_deviceDiscoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
            this, SLOT(addDevice(const QBluetoothDeviceInfo&)));
    connect(m_deviceDiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(deviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(m_deviceDiscoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));

//    SensorDataCollector _collector;
//    _collector.deviceSearch();
//    ui->accelerometerXPlot->appendPoint(QPointF(1, 1));
}

void MainWindow::deviceSearch()
{
    m_deviceDiscoveryAgent->start();
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::addDevice(const QBluetoothDeviceInfo &device)
{
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        qWarning() << "Discovered LE Device name: " << device.name() << " Address: "
                   << device.address().toString();

        if (QString::compare(device.name(), QString("HGinnoL")) == 0
                && m_leftFoot == 0) {
            qDebug() << "HGinnoL found";
            m_leftFoot = new QBluetoothDeviceInfo(device);
            m_leftFootController = new FootSensorController(*m_leftFoot);
            m_leftFootController->connectToDevice();
        }
        else if (QString::compare(device.name(), QString("HGinnoR")) == 0
                 && m_rightFoot == 0) {
            qDebug() << "HGinnoR found";
            m_rightFoot = new QBluetoothDeviceInfo(device);
            m_rightFootController = new FootSensorController(*m_rightFoot);
            m_rightFootController->connectToDevice();
        }
        else if (QString::compare(device.name(), QString("HGinnoG")) == 0
                 && m_accelerometer == 0) {
            qDebug() << "HGinnoG found";
            m_accelerometer = new QBluetoothDeviceInfo(device);
            m_accelerometerController = new AccelerometerController(*m_accelerometer);
            m_accelerometerController->connectToDevice();
        }
    }
}

void MainWindow::scanFinished()
{
//    if (m_leftFoot && m_rightFoot && m_accelerometer) {
//        m_leftFootController = new SensorController(*m_leftFoot, this);
//        m_rightFootController = new SensorController(*m_rightFoot, this);
//        m_accelerometerController = new SensorController(*m_accelerometer, this);
//    }
    qDebug() << "scan finished";
//    if (m_accelerometer) {
//        m_accelerometerController = new SensorController(*m_accelerometer, this);
//    }
//    else {
//        qWarning() << "not all devices are detected";
//    }

}


void MainWindow::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        qDebug() << "The Bluetooth adaptor is powered off, power it on before doing discovery.";
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        qDebug() << "Writing or reading from the device resulted in an error.";
    else
        qDebug() << "An unknown error has occurred.";
}
