#include <libusb-1.0/libusb.h>
#include <string>
#include <vector>
#include "device.h"

enum DevicesStatus
{
    NO_DEVICES,
    DEVICE_LIST_LOADED
};

class Devices
{
    protected:
        int errorCode;
        DevicesStatus status;
        ssize_t deviceCount;
        std::vector<Device> deviceList;

    public:
        Devices();

        //getters
        int getErrorCode();
        DevicesStatus getStatus();
        ssize_t getDeviceCount();
        std::vector<Device> getDeviceList();

        //deviceList CRUD
        void addDevice(Device);
        void removeDevice(Device);
        void clearDeviceList();
        Device getDeviceAtIndex(int);
        Device getDeviceByiSerialNumber(uint8_t);
};