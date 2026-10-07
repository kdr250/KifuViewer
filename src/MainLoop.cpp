#include "MainLoop.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

MainLoop::MainLoop() { }

bool MainLoop::Initialize()
{
    return mApplication.Initialize();
}

void MainLoop::RunLoop()
{
#ifdef __EMSCRIPTEN__
    auto callback = [](void* arg) {
        Application* pApp = reinterpret_cast<Application*>(arg);
        if (!pApp->IsRunning()) {
            emscripten_cancel_main_loop();
            pApp->Shutdown();
            return;
        }
        pApp->Loop();
    };
    emscripten_set_main_loop_arg(callback, &mApplication, 0, true);
#else
    while (mApplication.IsRunning()) {
        mApplication.Loop();
    }
    mApplication.Shutdown();
#endif
}

void MainLoop::Shutdown()
{
    mApplication.Shutdown();
}
