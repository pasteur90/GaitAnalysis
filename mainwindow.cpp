#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensordatacollector.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_deviceDiscoveryAgent(0),
    m_leftFoot(0), m_rightFoot(0), m_accelerometer(0),
    m_leftFootController(0), m_rightFootController(0), m_accelerometerController(0),
    m_leftFootFrontFile(0), m_leftFootBackFile(0), m_rightFootFrontFile(0), m_rightFootBackFile(0)
{
    ui->setupUi(this);
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(m_deviceDiscoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
            this, SLOT(addDevice(const QBluetoothDeviceInfo&)));
    connect(m_deviceDiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(deviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(m_deviceDiscoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));

    m_deviceDiscoveryAgent->start();
    // TODO: start time need to be updated every iteration
    startTime = QTime::currentTime().msecsSinceStartOfDay();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(startOver()));
    timer->start(5000);
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
            connect(m_leftFootController, SIGNAL(frontValue(int)),
                    this, SLOT(updateLeftFootFront(int)));
            connect(m_leftFootController, SIGNAL(backValue(int)),
                    this, SLOT(updateLeftFootBack(int)));

        }
        else if (QString::compare(device.name(), QString("HGinnoR")) == 0
                 && m_rightFoot == 0) {
            qDebug() << "HGinnoR found";
            m_rightFoot = new QBluetoothDeviceInfo(device);
            m_rightFootController = new FootSensorController(*m_rightFoot);
            m_rightFootController->connectToDevice();
            connect(m_rightFootController, SIGNAL(frontValue(int)),
                    this, SLOT(updateRightFootFront(int)));
            connect(m_rightFootController, SIGNAL(backValue(int)),
                    this, SLOT(updateRightFootBack(int)));
        }
        else if (QString::compare(device.name(), QString("HGinnoG")) == 0
                 && m_accelerometer == 0) {
            qDebug() << "HGinnoG found";
            m_accelerometer = new QBluetoothDeviceInfo(device);
            m_accelerometerController = new AccelerometerController(*m_accelerometer);
            m_accelerometerController->connectToDevice();
            connect(m_accelerometerController, SIGNAL(xValue(int)),
                    this, SLOT(updateAccelerometerX(int)));
            connect(m_accelerometerController, SIGNAL(yValue(int)),
                    this, SLOT(updateAccelerometerY(int)));
            connect(m_accelerometerController, SIGNAL(zValue(int)),
                    this, SLOT(updateAccelerometerZ(int)));

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

void MainWindow::updateLeftFootFront(const int val)
{
    ui->leftFootFrontPlot->appendPoint(QPointF(QTime::currentTime().msecsSinceStartOfDay() - startTime, val));
    ui->leftFootFrontPlot->replot();
}

void MainWindow::updateLeftFootBack(const int val)
{
    ui->leftFootBackPlot->appendPoint(QPointF(QTime::currentTime().msecsSinceStartOfDay() - startTime, val));
    ui->leftFootBackPlot->replot();
}

void MainWindow::updateRightFootFront(const int val)
{
    ui->rightFootFrontPlot->appendPoint(QPointF(QTime::currentTime().msecsSinceStartOfDay() - startTime, val));
    ui->rightFootFrontPlot->replot();
}

void MainWindow::updateRightFootBack(const int val)
{
    ui->rightFootBackPlot->appendPoint(QPointF(QTime::currentTime().msecsSinceStartOfDay() - startTime, val));
    ui->rightFootBackPlot->replot();
}

void MainWindow::updateAccelerometerX(const int val)
{
    ui->accelerometerXPlot->appendPoint(QPointF(QTime::currentTime().msecsSinceStartOfDay() - startTime, val));
    ui->accelerometerXPlot->replot();
}

void MainWindow::updateAccelerometerY(const int val)
{
    ui->accelerometerYPlot->appendPoint(QPointF(QTime::currentTime().msecsSinceStartOfDay() - startTime, val));
    ui->accelerometerYPlot->replot();
}

void MainWindow::updateAccelerometerZ(const int val)
{
    ui->accelerometerZPlot->appendPoint(QPointF(QTime::currentTime().msecsSinceStartOfDay() - startTime, val));
    ui->accelerometerZPlot->replot();
}

void MainWindow::startOver()
{
    ui->leftFootFrontPlot->clearPoints();
    ui->leftFootBackPlot->clearPoints();
    ui->rightFootFrontPlot->clearPoints();
    ui->rightFootBackPlot->clearPoints();
    ui->accelerometerXPlot->clearPoints();
    ui->accelerometerYPlot->clearPoints();
    ui->accelerometerZPlot->clearPoints();
    startTime = QTime::currentTime().msecsSinceStartOfDay();
}

