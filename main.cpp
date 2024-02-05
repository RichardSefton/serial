#include "src/terminal/terminal.h"
#include <signal.h> //For SIGINT handler (Ctrl+C)
#include <cstdlib> //for exit()
#include <thread>
#include <atomic>
#include <string.h>

Terminal terminal;
std::atomic<bool> keepRunning(true);
std::atomic<bool> isLibusbInitialized(false);
std::thread eventThread;
std::thread uiThread;

void eventHandlingThread()
{
    while(isLibusbInitialized.load())
    {
        libusb_handle_events_completed(NULL, NULL);
    }
}

void initializeLibusb() {
    if (libusb_init(NULL) == 0) { // Check for success
        isLibusbInitialized.store(true);
    }
}

void endMain()
{
    terminal.Kill();
    eventThread.detach();
}

void listenForDevices()
{
    libusb_hotplug_callback_handle handle;
    int rc = libusb_hotplug_register_callback(
        NULL,
        LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED | LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
        LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY,
        LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
        Terminal::HotPlugCallbackStatic, &terminal, &handle
    );

    if (LIBUSB_SUCCESS == rc)
    {
        if (!eventThread.joinable())
        {
            keepRunning.store(true);
            eventThread = std::thread(eventHandlingThread);
        }
    }
}

void uiHandlingThread() 
{
    int ch;
    while (keepRunning.load()) {
        ch = getch(); // Wait for user input
        if (ch == (int)24) { // ASCII code for Ctrl+x
            break;
        }
        terminal.HandleNavigation(ch);
        terminal.PrintDeviceList();
    }

    terminal.SetExit(true);
    // keepRunning.store(false);
}

int main()
{
    terminal.Run();

    initializeLibusb();
    listenForDevices();

    uiThread = std::thread(uiHandlingThread);
    uiThread.join();

    while(!terminal.GetExit());

    endMain();

    return 0;
}