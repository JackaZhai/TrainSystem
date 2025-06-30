#ifndef PASSENGERTRAFFICVOLUME_H
#define PASSENGERTRAFFICVOLUME_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class PassengerTrafficVolumeData;

class PassengerTrafficVolume
{
    Q_OBJECT
    QML_ELEMENT
public:
    PassengerTrafficVolume();
    PassengerTrafficVolume(const PassengerTrafficVolume &);
    PassengerTrafficVolume(PassengerTrafficVolume &&);
    PassengerTrafficVolume &operator=(const PassengerTrafficVolume &);
    PassengerTrafficVolume &operator=(PassengerTrafficVolume &&);
    ~PassengerTrafficVolume();

private:
    QSharedDataPointer<PassengerTrafficVolumeData> data;
};

#endif // PASSENGERTRAFFICVOLUME_H
