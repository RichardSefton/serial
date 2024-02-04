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
    DEVICE_LIST,
    SERIAL_MONITOR,
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

        //ui
        void PrintDeviceList();
        void HandleNavigation(int);
        void UpdateInstructionSet();
        void DrawOptions();
};