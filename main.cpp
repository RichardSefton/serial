#include "src/terminal/terminal.h"
#include <signal.h> //For SIGINT handler (Ctrl+C)
#include <cstdlib> //for exit()

Terminal terminal;

void signalHandler(int signum)
{
    terminal.Kill();
    exit(signum);
}

int main()
{
    signal(SIGINT, signalHandler);

    terminal.Run();
    int ch;

    while ((ch = getch()) != (int)24)
    {
        
    }

    terminal.Kill();
    return 0;
}