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
        Device(libusb_device_descriptor*);

        //setters
        void setIdVendor(uint16_t);
        void setIdProduct(uint16_t);
        void setBcdUSB(uint16_t);
        void setBDeviceClass(uint16_t);
        void setBDeviceSubClass(uint16_t);
        void setBDeviceProtocol(uint8_t);
        void setBMaxPacketSize0(uint8_t);
        void setIManufacturer(uint8_t);
        void setIProduct(uint8_t);
        void setIManufacturerBuffer(unsigned char*, size_t);
        void setIProductBuffer(unsigned char*, size_t);
        void setISerialNumber(uint8_t);
        void setBNumConfigurations(uint8_t);

        //getters
        uint16_t getIdVendor();
        uint16_t getIdProduct();
        uint16_t getBcdUSB();
        uint16_t getBDeviceClass();
        uint16_t getBDeviceSubClass();
        uint8_t getBDeviceProtocol();
        uint8_t getBMaxPacketSize0();
        uint8_t getIManufacturer();
        uint8_t getIProduct();
        unsigned char* getIManufacturerBuffer();
        unsigned char* getIProductBuffer();
        uint8_t getISerialNumber();
        uint8_t getBNumConfigurations();


};