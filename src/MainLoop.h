#pragma once

#include "application/Application.h"

class MainLoop {
public:
    MainLoop();

    bool Initialize();
    void RunLoop();
    void Shutdown();

private:
    Application mApplication;
};
