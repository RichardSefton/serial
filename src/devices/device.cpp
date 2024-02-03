#include "device.h"
#include <string.h>

Device::Device(libusb_device_descriptor* device)
{
    this->idVendor = device->idVendor;
    this->idProduct = device->idProduct;
    this->bcdUSB = device->bcdUSB;
    this->bDeviceClass = device->bDeviceClass;
    this->bDeviceSubClass = device->bDeviceSubClass;
    this->bDeviceProtocol = device->bDeviceProtocol;
    this->bMaxPacketSize0 = device->bMaxPacketSize0;
    this->iManufacturer = device->iManufacturer;
    this->iProduct = device->iProduct;
    this->iSerialNumber = device->iSerialNumber;
    this->bNumConfigurations = device->bNumConfigurations;
}

//setters
void Device::SetIdVendor(uint16_t idVendor)
{
    this->idVendor = idVendor;
}
void Device::SetIdProduct(uint16_t idProduct)
{
    this->idProduct = idProduct;
}
void Device::SetBcdUSB(uint16_t bcdUSB)
{
    this->bcdUSB = bcdUSB;
}
void Device::SetBDeviceClass(uint16_t bDeviceClass)
{
    this->bDeviceClass = bDeviceClass;
}
void Device::SetBDeviceSubClass(uint16_t bDeviceSubClass)
{
    this->bDeviceSubClass = bDeviceSubClass;
}
void Device::SetBDeviceProtocol(uint8_t bDeviceProtocol)
{
    this->bDeviceProtocol = bDeviceProtocol;
}
void Device::SetBMaxPacketSize0(uint8_t bMaxPacketSize0)
{
    this->bMaxPacketSize0 = bMaxPacketSize0;
}
void Device::SetIManufacturer(uint8_t iManufacturer)
{
    this->iManufacturer = iManufacturer;
}
void Device::SetIProduct(uint8_t iProduct)
{
    this->iProduct = iProduct;
}
void Device::SetIManufacturerBuffer(unsigned char *iManufacturerBuffer, size_t length)
{
    //because its a pointer we want to make a local copy
    size_t copyLength = (length < sizeof(this->iManufacturerBuffer)) ? length : sizeof(this->iManufacturerBuffer) - 1;
    memcpy(this->iManufacturerBuffer, iManufacturerBuffer, copyLength);
    this->iManufacturerBuffer[copyLength] = '\0';
}
void Device::SetIProductBuffer(unsigned char *iProductBuffer, size_t length)
{
    //because its a pointer we want to make a local copy
    size_t copyLength = (length < sizeof(this->iProductBuffer)) ? length : sizeof(this->iProductBuffer) - 1;
    memcpy(this->iProductBuffer, iProductBuffer, copyLength);
    this->iProductBuffer[copyLength] = '\0';
}
void Device::SetISerialNumber(uint8_t iSerialNumber)
{
    this->iSerialNumber = iSerialNumber;
}
void Device::SetBNumConfigurations(uint8_t bNumConfigurations)
{
    this->bNumConfigurations = bNumConfigurations;
}

//getters
uint16_t Device::GetIdVendor()
{
    return this->idVendor;
}
uint16_t Device::GetIdProduct()
{
    return this->idProduct;
}
uint16_t Device::GetBcdUSB()
{
    return this->bcdUSB;
}
uint16_t Device::GetBDeviceClass()
{
    return this->bDeviceClass;
}
uint16_t Device::GetBDeviceSubClass()
{
    return this->bDeviceSubClass;
}
uint8_t Device::GetBDeviceProtocol()
{
    return this->bDeviceProtocol;
}
uint8_t Device::GetBMaxPacketSize0()
{
    return this->bMaxPacketSize0;
}
uint8_t Device::GetIManufacturer()
{
    return this->iManufacturer;
}
uint8_t Device::GetIProduct()
{
    return this->iProduct;
}
unsigned char* Device::GetIManufacturerBuffer()
{
    return this->iManufacturerBuffer;
}
unsigned char* Device::GetIProductBuffer()
{
    return this->iProductBuffer;
}
uint8_t Device::GetISerialNumber()
{
    return this->iSerialNumber;
}
uint8_t Device::GetBNumConfigurations()
{
    return this->bNumConfigurations;
}