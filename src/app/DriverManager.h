#pragma once 
#include <vector>
#include <mutex>
#include "SerialDriver.h"
class SerialDirver;
class SerialListener;

SERIAL_DRIVER_CLASS(Serial1);
SERIAL_DRIVER_CLASS(Serial2);

class DriverManager
{
public:

    DriverManager();
    ~DriverManager();

    void addDriver(DriverBase *driver);
private:

    Serial1* _serial1 =nullptr;
    Serial2* _serial2 =nullptr;
    std::mutex _mt;

    std::vector<DriverBase *>_driverList;
};





