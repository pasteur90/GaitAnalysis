#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sensorcontroller.h"
#include "accelerometercontroller.h"
#include "footsensorcontroller.h"

#include <QMainWindow>
#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QList>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void deviceSearch();
private slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);
    void scanFinished();

private:
    Ui::MainWindow *ui;
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QBluetoothDeviceInfo *m_leftFoot;
    QBluetoothDeviceInfo *m_rightFoot;
    QBluetoothDeviceInfo *m_accelerometer;
    FootSensorController *m_leftFootController;
    FootSensorController *m_rightFootController;
    AccelerometerController *m_accelerometerController;

};

#endif // MAINWINDOW_H
