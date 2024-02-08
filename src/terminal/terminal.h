#pragma once

#include <ncurses.h>
#include "devices.h"
#include <string>

enum SerialState {
    RUNNING,
    STOPPED
};

enum State {
    ENABLED,
    DISABLED
};

enum InstructionSet {
    INST_NO_DEVICES,
    INST_DEVICE_LIST,
    INST_SERIAL_MONITOR,
};

class Terminal {
    protected:
        SerialState state;
        State linebuffering;
        State keypressecho;
        State functionkeys;
        State arrowkeys;
        Devices devices;
        State colour;
        int yPos;
        int xPos;
        int tableStartPos;
        InstructionSet instructionSet;
        std::vector<std::string> instructionOptions;
        bool exit;

    public: 
        Terminal();

        void Run();
        void Kill();

        void DisableLineBuffering();
        void EnableLineBuffering();

        void DisableKeyPressEcho();
        void EnableKeyPressEcho();
        
        void DisableFunctionAndArrowKeys();
        void EnableFunctionAndArrowKeys();

        void DisableColour();
        void EnableColour();

        SerialState GetState();
        State GetLineBuffering();
        State GetKeyPressEcho();
        State GetFunctionKeys();
        State GetArrowKeys();

        //data
        void LoadDevices();
        // int HotPlugCallback(struct libusb_context*, struct libusb_device*, libusb_hotplug_event, void*);
        void HotPlugHandler(libusb_context*, libusb_device*, libusb_hotplug_event);

        // Static bridge function
        static int LIBUSB_CALL HotPlugCallbackStatic(libusb_context*, libusb_device*, libusb_hotplug_event, void*);

        //ui
        void EmptyDeviceList();
        void PrintDeviceList();
        void HandleNavigation(int);
        void UpdateInstructionSet();
        void DrawOptions();
        void SetExit(bool);
        bool GetExit();
        void BaudRateWindow();
        void DrawSerialMonitor();
};