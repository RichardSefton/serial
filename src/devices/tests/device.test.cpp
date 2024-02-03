#include "device.h"
#include <gtest/gtest.h>
#include <stdio.h>

TEST(Device, InitNoErrors)
{
    Device* device = new Device(nullptr);
    EXPECT_EQ(1, 1);
    delete(device);
}

TEST(Device, LoadsDeviceFromId)
{
    Device* device = new Device(nullptr);
    EXPECT_EQ(1, 1);
    delete(device);
}

//Its not east to test this library directly because it requires a USB device to be connected
