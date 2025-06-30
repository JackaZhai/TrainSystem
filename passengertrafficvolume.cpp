#include "passengertrafficvolume.h"

#include <utility>

class PassengerTrafficVolumeData : public QSharedData
{
public:
};

PassengerTrafficVolume::PassengerTrafficVolume()
    : data(new PassengerTrafficVolumeData)
{}

PassengerTrafficVolume::PassengerTrafficVolume(const PassengerTrafficVolume &rhs)
    : data{rhs.data}
{}

PassengerTrafficVolume::PassengerTrafficVolume(PassengerTrafficVolume &&rhs)
    : data{std::move(rhs.data)}
{}

PassengerTrafficVolume &PassengerTrafficVolume::operator=(const PassengerTrafficVolume &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

PassengerTrafficVolume &PassengerTrafficVolume::operator=(PassengerTrafficVolume &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

PassengerTrafficVolume::~PassengerTrafficVolume() {}
