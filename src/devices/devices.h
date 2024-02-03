#pragma once

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
        int GetErrorCode();
        DevicesStatus GetStatus();
        ssize_t GetDeviceCount();
        std::vector<Device> GetDeviceList();

        //deviceList CRUD
        void AddDevice(Device);
        void RemoveDevice(Device);
        void ClearDeviceList();
        Device GetDeviceAtIndex(int);
        Device GetDeviceByiSerialNumber(uint8_t);
};