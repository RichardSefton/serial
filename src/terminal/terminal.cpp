#include "terminal.h"
#include <ncurses.h>
#include "device.h"
#include "devices.h"

Terminal::Terminal() :
    state(SerialState::STOPPED),
    linebuffering(State::ENABLED),
    keypressecho(State::ENABLED),
    functionkeys(State::DISABLED),
    arrowkeys(State::DISABLED),
    devices(Devices()),
    colour(State::DISABLED),
    yPos(1),
    xPos(0),
    tableStartPos(1),
    instructionSet(InstructionSet::INST_DEVICE_LIST),
    exit(false)
{
}

void Terminal::Run()
{
    initscr();
    DisableLineBuffering();
    EnableFunctionAndArrowKeys();
    DisableKeyPressEcho();

    this->LoadDevices();
    this->PrintDeviceList();
    this->UpdateInstructionSet();

    this->state = SerialState::RUNNING;
    refresh();
}

void Terminal::Kill()
{
    endwin();
    this->state = SerialState::STOPPED;
    this->linebuffering = State::DISABLED;
    this->keypressecho = State::DISABLED;
    this->functionkeys = State::DISABLED;
    this->arrowkeys = State::DISABLED;
}

void Terminal::DisableLineBuffering()
{
    if (this->linebuffering == State::ENABLED)
    {
        this->linebuffering = State::DISABLED;
        cbreak();
    }

}

void Terminal::EnableLineBuffering()
{
    if (this->linebuffering == State::DISABLED)
    {
        this->linebuffering = State::ENABLED;
        nocbreak();
    }
}

void Terminal::DisableKeyPressEcho()
{
    if (this->keypressecho == State::ENABLED)
    {
        this->keypressecho = State::DISABLED;
        noecho();
    }
}

void Terminal::EnableKeyPressEcho()
{
    if (this->keypressecho == State::DISABLED)
    {
        this->keypressecho = State::ENABLED;
        echo();
    }
}

void Terminal::DisableFunctionAndArrowKeys()
{
    if (this->functionkeys == State::ENABLED && this->arrowkeys == State::ENABLED)
    {
        this->functionkeys = State::DISABLED;
        this->arrowkeys = State::DISABLED;
        keypad(stdscr, FALSE);
    }
}

void Terminal::EnableFunctionAndArrowKeys()
{
    if (this->functionkeys == State::DISABLED && this->arrowkeys == State::DISABLED)
    {
        this->functionkeys = State::ENABLED;
        this->arrowkeys = State::ENABLED;
        keypad(stdscr, TRUE);
    }
}

void Terminal::DisableColour()
{
    if (this->colour == State::ENABLED)
    {
        this->colour = State::DISABLED;
        start_color();
    }
}

void Terminal::EnableColour()
{
    if (this->colour == State::DISABLED)
    {
        this->colour = State::ENABLED;
        start_color();
    }
}

SerialState Terminal::GetState()
{
    return this->state;
}

State Terminal::GetLineBuffering()
{
    return this->linebuffering;
}

State Terminal::GetKeyPressEcho()
{
    return this->keypressecho;
}

State Terminal::GetFunctionKeys()
{
    return this->functionkeys;
}

State Terminal::GetArrowKeys()
{
    return this->arrowkeys;
}

void Terminal::LoadDevices()
{
    Devices devices;
    this->devices = devices;
    if (this->devices.GetDeviceCount() == 0)
    {
        this->instructionSet = InstructionSet::INST_NO_DEVICES;
    }
}

void Terminal::HotPlugHandler(struct libusb_context *ctx, struct libusb_device *device, libusb_hotplug_event event) 
{
    if (event == LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED || event == LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT) 
    {
        this->EmptyDeviceList();
        this->yPos = 1;
        this->LoadDevices();
        this->PrintDeviceList();
        this->UpdateInstructionSet();
        this->DrawOptions();
    }
}

int LIBUSB_CALL Terminal::HotPlugCallbackStatic(libusb_context *ctx, libusb_device *device, libusb_hotplug_event event, void *user_data) 
{
    // Forward the call to the instance method
    Terminal* terminal = static_cast<Terminal*>(user_data);
    terminal->HotPlugHandler(ctx, device, event);
    return 0; // Return 0 to indicate success
}

void Terminal::EmptyDeviceList()
{
    int width = getmaxx(stdscr); 
    attron(COLOR_PAIR(2));
    for (int i = 0; i < this->devices.GetDeviceCount(); i++)
    {
        mvhline(i + this->tableStartPos, 0, ' ', width);
    }
    attroff(COLOR_PAIR(2));
    refresh();
}

void Terminal::PrintDeviceList()
{
    this->EnableColour();

    //ui setup
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);

    int width = getmaxx(stdscr);  // Get the width of the terminal

    //table headers
    attron(COLOR_PAIR(1));
    mvhline(0, 0, ' ', width);  
    mvprintw(0, 0, "Device ID");
    mvprintw(0, 15, "Device Name");
    mvprintw(0, 35, "Device Type");
    attroff(COLOR_PAIR(1));

    //table data
    if (this->devices.GetDeviceCount() == 0)
    {
        attron(COLOR_PAIR(2));
        mvhline(1, 0, ' ', width);
        mvprintw(1, 0, "No devices found");
        attroff(COLOR_PAIR(2));
    }
    else
    {
        std::vector<Device> devices = this->devices.GetDeviceList();
        for (int i = 0; i < devices.size(); i++)
        {
            i == this->devices.GetActiveDeviceIndex() ? attron(COLOR_PAIR(3)) : attroff(COLOR_PAIR(2));
            mvhline(i + this->tableStartPos, 0, ' ', width);
            mvprintw(i + this->tableStartPos, 0, "%s", std::to_string(devices[i].GetIdProduct()).c_str());
            unsigned char* pBuffer = devices[i].GetIProductBuffer();
            mvprintw(i + this->tableStartPos, 15, "%s", reinterpret_cast<const char*>(pBuffer));
            unsigned char* mBuffer = devices[i].GetIManufacturerBuffer();
            mvprintw(i + this->tableStartPos, 35, "%s", reinterpret_cast<const char*>(mBuffer));
            i == this->devices.GetActiveDeviceIndex() ? attroff(COLOR_PAIR(3)) : attroff(COLOR_PAIR(2));
        }
    }

    refresh();
}

void Terminal::HandleNavigation(int ch)
{
    move(this->yPos, this->xPos);

    if (ch == KEY_UP)
    {
        if (this->yPos > this->tableStartPos)
        {
            this->yPos--;
            this->devices.SetActiveDevice(this->yPos - this->tableStartPos);
        }
    }
    if (ch == KEY_DOWN)
    {
        if (this->yPos < this->devices.GetDeviceCount())
        {
            this->yPos++;
            this->devices.SetActiveDevice(this->yPos - this->tableStartPos);
        }
    }

    move(this->yPos, this->xPos);

    refresh();
}

void Terminal::UpdateInstructionSet()
{
    this->instructionOptions.clear();
    if (this->instructionSet == InstructionSet::INST_NO_DEVICES)
    {
        this->instructionOptions.push_back("[Ctrl+x/c] Quit");
    }

    if (this->instructionSet == InstructionSet::INST_DEVICE_LIST)
    {
        this->instructionOptions.push_back("[Ctrl+c] Quit");
        this->instructionOptions.push_back("[Enter] Select Device");
        this->instructionOptions.push_back("[Arrow Keys] Navigate");
        this->instructionOptions.push_back("[F2] Baud Rate");
    }

    if (this->instructionSet == InstructionSet::INST_SERIAL_MONITOR)
    {
        this->instructionOptions.push_back("[Ctrl+c] Quit");
        this->instructionOptions.push_back("[F3] Device List");
        this->instructionOptions.push_back("[F2] Baud Rate");
        this->instructionOptions.push_back("[F4] Monitor");
        this->instructionOptions.push_back("[F6] ASCII");
        this->instructionOptions.push_back("[F7] Hex");
        this->instructionOptions.push_back("[Enter] Send");
    }

    this->DrawOptions();
}

void Terminal::DrawOptions()
{
    // Calculate spacing based on the number of options and the screen width
    int spacing = COLS / this->instructionOptions.size();

    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    
    attron(COLOR_PAIR(4));
    int width = getmaxx(stdscr);  // Get the width of the terminal
    mvhline(LINES - 2, 0, '-', width);
    mvhline(LINES - 1, 0, ' ', width);
    for (int i = 0; i < this->instructionOptions.size(); i++) {
        // Move to the correct position and print each option
        // We use LINES - 1 to get the bottom row of the terminal
        mvprintw(LINES - 1, i * spacing, "%s", this->instructionOptions[i].c_str());
    }
    attroff(COLOR_PAIR(4));
    refresh();  // Update the screen
}

void Terminal::SetExit(bool exit)
{
    this->exit = exit;
}

bool Terminal::GetExit()
{
    return this->exit;
}

