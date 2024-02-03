#include "terminal.h"
#include <ncurses.h>
#include "device.h"
#include "devices.h"

Terminal::Terminal()
{
    state = SerialState::STOPPED;
    linebuffering = State::ENABLED;
    keypressecho = State::ENABLED;
    functionkeys = State::DISABLED;
    arrowkeys = State::DISABLED;
    colour = State::DISABLED;
}

void Terminal::Run()
{
    initscr();
    DisableLineBuffering();
    EnableFunctionAndArrowKeys();
    DisableKeyPressEcho();

    this->LoadDevices();

    if (this->devices.GetDeviceCount() > 0)
    {
        this->PrintDeviceList();
    }

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
}

void Terminal::PrintDeviceList()
{
    this->EnableColour();

    //ui setup
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    int width = getmaxx(stdscr);  // Get the width of the terminal

    //table headers
    attron(COLOR_PAIR(1));
    mvhline(0, 0, ' ', width);  
    mvprintw(0, 0, "Device ID");
    mvprintw(0, 15, "Device Name");
    mvprintw(0, 35, "Device Type");
    attroff(COLOR_PAIR(1));

    //table data
    attron(COLOR_PAIR(2));
    std::vector<Device> devices = this->devices.GetDeviceList();
    for (int i = 0; i < devices.size(); i++)
    {
        mvprintw(i + 1, 0, "%s", std::to_string(devices[i].GetIdProduct()).c_str());
        unsigned char* pBuffer = devices[i].GetIProductBuffer();
        mvprintw(i + 1, 15, "%s", reinterpret_cast<const char*>(pBuffer));
        unsigned char* mBuffer = devices[i].GetIManufacturerBuffer();
        mvprintw(i + 1, 35, "%s", reinterpret_cast<const char*>(mBuffer));
    }
    attroff(COLOR_PAIR(2));

    refresh();
}