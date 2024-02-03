#include "devices.h"
#include <gtest/gtest.h>
#include <stdio.h>

TEST(Devices, InitNoErrors)
{
    Devices* devices = new Devices();
    EXPECT_EQ(1, 1);
    delete(devices);
}

TEST(Devices, LoadsDevices)
{
    //Note: This test requires a USB device to be connected
    //Device test written for is a AVR Curiosity 1627
    Devices* devices = new Devices();
    
    EXPECT_GE(devices->GetErrorCode(), 0);
    EXPECT_EQ(devices->GetDeviceCount(), 1);
    
    delete(devices);
}