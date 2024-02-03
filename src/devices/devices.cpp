#include "devices.h"
#include <iostream>

Devices::Devices() :
    errorCode(0),
    deviceCount(0)
{
    libusb_context *ctx = nullptr;
    this->errorCode = libusb_init(&ctx);
    if (this->errorCode < 0)
    {
        //we have an error so return
        return;
    }

    //Get the list of devices
    ssize_t cnt;
    libusb_device **list;
    cnt = libusb_get_device_list(ctx, &list);
    for (ssize_t i = 0; i < cnt; i++) 
    {
        libusb_device *device = list[i];
        libusb_device_descriptor desc;

        if (libusb_get_device_descriptor(device, &desc) < 0) 
        {
            continue;
        }

        Device newDevice {&desc};

        libusb_device_handle *handle;
        if (libusb_open(device, &handle) == LIBUSB_SUCCESS) {
            unsigned char buffer[256]; // Buffer for string descriptor

            if (desc.iManufacturer) {
                if (libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, buffer, sizeof(buffer)) > 0) {
                    newDevice.setIManufacturerBuffer(buffer, sizeof(buffer));
                }
            }

            if (desc.iProduct) {
                if (libusb_get_string_descriptor_ascii(handle, desc.iProduct, buffer, sizeof(buffer)) > 0) {
                    newDevice.setIProductBuffer(buffer, sizeof(buffer));
                }
            }

            this->addDevice(newDevice);

            libusb_close(handle);
        }
    }

    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
}

//getters
int Devices::getErrorCode()
{
    return this->errorCode;
}
DevicesStatus Devices::getStatus()
{
    return this->status;
}
ssize_t Devices::getDeviceCount()
{
    return this->deviceCount;
}
std::vector<Device> Devices::getDeviceList()
{
    return this->deviceList;
}

//deviceList CRUD
void Devices::addDevice(Device device)
{
    this->deviceList.push_back(device);
    this->deviceCount++;
}
void Devices::removeDevice(Device device)
{
    //find the index of the device and remove it from the vector
    for (std::vector<Device>::iterator it = this->deviceList.begin(); it != this->deviceList.end(); ++it)
    {
        if (it->getISerialNumber() == device.getISerialNumber())
        {
            this->deviceList.erase(it);
            this->deviceCount--;
            break;
        }
    }
}
void Devices::clearDeviceList()
{
    this->deviceList.clear();
}
Device Devices::getDeviceAtIndex(int index)
{
    return this->deviceList.at(index);
}
Device Devices::getDeviceByiSerialNumber(uint8_t iSerialNumber)
{
    for (Device device : this->deviceList)
    {
        if (device.getISerialNumber() == iSerialNumber)
        {
            return device;
        }
    }
    return Device(nullptr);
}