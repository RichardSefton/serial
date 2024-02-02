#include <ncurses.h>

enum SerialState {
    RUNNING,
    STOPPED
};

enum State {
    ENABLED,
    DISABLED
};

class Terminal {
    protected:
        SerialState state;
        State linebuffering;
        State keypressecho;
        State functionkeys;
        State arrowkeys;

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

        SerialState GetState();
        State GetLineBuffering();
        State GetKeyPressEcho();
        State GetFunctionKeys();
        State GetArrowKeys();
};