#include "terminal.h"
#include <ncurses.h>

Terminal::Terminal()
{
    state = SerialState::STOPPED;
    linebuffering = State::ENABLED;
    keypressecho = State::ENABLED;
    functionkeys = State::DISABLED;
    arrowkeys = State::DISABLED;
}

void Terminal::Run()
{
    initscr();
    DisableLineBuffering();
    EnableFunctionAndArrowKeys();
    DisableKeyPressEcho();

    printw("Hello World !!! Press Ctrl+X or Ctrl+C to exit");
    
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