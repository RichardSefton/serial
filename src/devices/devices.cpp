#include "devices.h"
#include <iostream>

Devices::Devices() :
    errorCode(0),
    deviceCount(0),
    activeDeviceIndex(0)
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
                    newDevice.SetIManufacturerBuffer(buffer, sizeof(buffer));
                }
            }

            if (desc.iProduct) {
                if (libusb_get_string_descriptor_ascii(handle, desc.iProduct, buffer, sizeof(buffer)) > 0) {
                    newDevice.SetIProductBuffer(buffer, sizeof(buffer));
                }
            }

            this->AddDevice(newDevice);

            libusb_close(handle);
        }
    }

    if (this->deviceList.size() > 0)
    {
        this->status = DEVICE_LIST_LOADED;
        activeDevice = this->deviceList.at(this->activeDeviceIndex);
    }
    else
    {
        this->status = NO_DEVICES;
    }

    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
}

//setters
void Devices::SetActiveDevice(int index)
{
    this->activeDeviceIndex = index;
    Device device = this->deviceList.at(index);
    this->activeDevice = device;
}
void Devices::SetActiveDeviceBaudRate(int baudRate)
{
    this->activeDevice.SetBaudRate(baudRate);
    this->UpdateDeviceAtIndex(this->activeDeviceIndex, this->activeDevice);
}

//getters
int Devices::GetErrorCode()
{
    return this->errorCode;
}
DevicesStatus Devices::GetStatus()
{
    return this->status;
}
ssize_t Devices::GetDeviceCount()
{
    return this->deviceCount;
}
std::vector<Device> Devices::GetDeviceList()
{
    return this->deviceList;
}
int Devices::GetActiveDeviceIndex()
{
    return this->activeDeviceIndex;
}

//deviceList CRUD
void Devices::AddDevice(Device device)
{
    this->deviceList.push_back(device);
    this->deviceCount++;
}
void Devices::RemoveDevice(Device device)
{
    //find the index of the device and remove it from the vector
    for (std::vector<Device>::iterator it = this->deviceList.begin(); it != this->deviceList.end(); ++it)
    {
        if (it->GetISerialNumber() == device.GetISerialNumber())
        {
            this->deviceList.erase(it);
            this->deviceCount--;
            break;
        }
    }
}
void Devices::ClearDeviceList()
{
    this->deviceList.clear();
}
Device Devices::GetDeviceAtIndex(int index)
{
    return this->deviceList.at(index);
}
Device Devices::GetDeviceByiSerialNumber(uint8_t iSerialNumber)
{
    for (Device device : this->deviceList)
    {
        if (device.GetISerialNumber() == iSerialNumber)
        {
            return device;
        }
    }
    return Device(nullptr);
}

void Devices::UpdateDeviceAtIndex(int index, Device device)
{
    this->deviceList.at(index) = device;
}
