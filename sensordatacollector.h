#ifndef SENSORDATACOLLECTOR_H
#define SENSORDATACOLLECTOR_H

#include <QObject>

class SensorDataCollector : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataCollector(QObject *parent = 0);

signals:

public slots:
};

#endif // SENSORDATACOLLECTOR_H
