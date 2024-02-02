#include "terminal.h"
#include <gtest/gtest.h>
#include <stdio.h>

TEST(Terminal, InitNoErrors) {
    Terminal* terminal = new Terminal();
    EXPECT_EQ(terminal->GetState(), SerialState::STOPPED);
    EXPECT_EQ(terminal->GetLineBuffering(), State::ENABLED);
    EXPECT_EQ(terminal->GetKeyPressEcho(), State::ENABLED);
    EXPECT_EQ(terminal->GetFunctionKeys(), State::DISABLED);
    EXPECT_EQ(terminal->GetArrowKeys(), State::DISABLED);

    delete(terminal);
}   

TEST(Terminal, RunNoErrors) {
    Terminal* terminal = new Terminal();
    terminal->Run();
    EXPECT_EQ(1, 1);
    terminal->Kill();
    delete(terminal);
}

TEST(Terminal, RunSucceeds)
{
    Terminal* terminal = new Terminal();
    terminal->Run();
    EXPECT_EQ(terminal->GetState(), SerialState::RUNNING);
    EXPECT_EQ(terminal->GetLineBuffering(), State::DISABLED);
    EXPECT_EQ(terminal->GetKeyPressEcho(), State::DISABLED);
    EXPECT_EQ(terminal->GetFunctionKeys(), State::ENABLED);
    EXPECT_EQ(terminal->GetArrowKeys(), State::ENABLED);
    terminal->Kill();
    delete(terminal);
}

TEST(Terminal, KillSucceeds)
{
    Terminal* terminal = new Terminal();
    terminal->Kill();
    EXPECT_EQ(terminal->GetState(), SerialState::STOPPED);
    EXPECT_EQ(terminal->GetLineBuffering(), State::DISABLED);
    EXPECT_EQ(terminal->GetKeyPressEcho(), State::DISABLED);
    EXPECT_EQ(terminal->GetFunctionKeys(), State::DISABLED);
    EXPECT_EQ(terminal->GetArrowKeys(), State::DISABLED);
    delete(terminal);
}