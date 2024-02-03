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
void Device::setIdVendor(uint16_t idVendor)
{
    this->idVendor = idVendor;
}
void Device::setIdProduct(uint16_t idProduct)
{
    this->idProduct = idProduct;
}
void Device::setBcdUSB(uint16_t bcdUSB)
{
    this->bcdUSB = bcdUSB;
}
void Device::setBDeviceClass(uint16_t bDeviceClass)
{
    this->bDeviceClass = bDeviceClass;
}
void Device::setBDeviceSubClass(uint16_t bDeviceSubClass)
{
    this->bDeviceSubClass = bDeviceSubClass;
}
void Device::setBDeviceProtocol(uint8_t bDeviceProtocol)
{
    this->bDeviceProtocol = bDeviceProtocol;
}
void Device::setBMaxPacketSize0(uint8_t bMaxPacketSize0)
{
    this->bMaxPacketSize0 = bMaxPacketSize0;
}
void Device::setIManufacturer(uint8_t iManufacturer)
{
    this->iManufacturer = iManufacturer;
}
void Device::setIProduct(uint8_t iProduct)
{
    this->iProduct = iProduct;
}
void Device::setIManufacturerBuffer(unsigned char *iManufacturerBuffer, size_t length)
{
    //because its a pointer we want to make a local copy
    size_t copyLength = (length < sizeof(this->iManufacturerBuffer)) ? length : sizeof(this->iManufacturerBuffer) - 1;
    memcpy(this->iManufacturerBuffer, iManufacturerBuffer, copyLength);
    this->iManufacturerBuffer[copyLength] = '\0';
}
void Device::setIProductBuffer(unsigned char *iProductBuffer, size_t length)
{
    //because its a pointer we want to make a local copy
    size_t copyLength = (length < sizeof(this->iProductBuffer)) ? length : sizeof(this->iProductBuffer) - 1;
    memcpy(this->iProductBuffer, iProductBuffer, copyLength);
    this->iProductBuffer[copyLength] = '\0';
}
void Device::setISerialNumber(uint8_t iSerialNumber)
{
    this->iSerialNumber = iSerialNumber;
}
void Device::setBNumConfigurations(uint8_t bNumConfigurations)
{
    this->bNumConfigurations = bNumConfigurations;
}

//getters
uint16_t Device::getIdVendor()
{
    return this->idVendor;
}
uint16_t Device::getIdProduct()
{
    return this->idProduct;
}
uint16_t Device::getBcdUSB()
{
    return this->bcdUSB;
}
uint16_t Device::getBDeviceClass()
{
    return this->bDeviceClass;
}
uint16_t Device::getBDeviceSubClass()
{
    return this->bDeviceSubClass;
}
uint8_t Device::getBDeviceProtocol()
{
    return this->bDeviceProtocol;
}
uint8_t Device::getBMaxPacketSize0()
{
    return this->bMaxPacketSize0;
}
uint8_t Device::getIManufacturer()
{
    return this->iManufacturer;
}
uint8_t Device::getIProduct()
{
    return this->iProduct;
}
unsigned char* Device::getIManufacturerBuffer()
{
    return this->iManufacturerBuffer;
}
unsigned char* Device::getIProductBuffer()
{
    return this->iProductBuffer;
}
uint8_t Device::getISerialNumber()
{
    return this->iSerialNumber;
}
uint8_t Device::getBNumConfigurations()
{
    return this->bNumConfigurations;
}