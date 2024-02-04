#pragma once

#include <libusb-1.0/libusb.h>
#include <libusb-1.0/libusb.h>

class Device
{
    protected:
        uint16_t idVendor;
        uint16_t idProduct;
        uint16_t bcdUSB;
        uint16_t bDeviceClass;
        uint16_t bDeviceSubClass;
        uint8_t bDeviceProtocol;
        uint8_t bMaxPacketSize0;
        uint8_t iManufacturer;
        uint8_t iProduct;
        unsigned char iManufacturerBuffer[256];
        unsigned char iProductBuffer[256];
        uint8_t iSerialNumber;
        uint8_t bNumConfigurations;
    
    public:
        Device();
        Device(libusb_device_descriptor*);

        //setters
        void SetIdVendor(uint16_t);
        void SetIdProduct(uint16_t);
        void SetBcdUSB(uint16_t);
        void SetBDeviceClass(uint16_t);
        void SetBDeviceSubClass(uint16_t);
        void SetBDeviceProtocol(uint8_t);
        void SetBMaxPacketSize0(uint8_t);
        void SetIManufacturer(uint8_t);
        void SetIProduct(uint8_t);
        void SetIManufacturerBuffer(unsigned char*, size_t);
        void SetIProductBuffer(unsigned char*, size_t);
        void SetISerialNumber(uint8_t);
        void SetBNumConfigurations(uint8_t);

        //getters
        uint16_t GetIdVendor();
        uint16_t GetIdProduct();
        uint16_t GetBcdUSB();
        uint16_t GetBDeviceClass();
        uint16_t GetBDeviceSubClass();
        uint8_t GetBDeviceProtocol();
        uint8_t GetBMaxPacketSize0();
        uint8_t GetIManufacturer();
        uint8_t GetIProduct();
        unsigned char* GetIManufacturerBuffer();
        unsigned char* GetIProductBuffer();
        uint8_t GetISerialNumber();
        uint8_t GetBNumConfigurations();


};