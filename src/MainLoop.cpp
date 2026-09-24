#include "MainLoop.h"

#include <algorithm>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

MainLoop::MainLoop() { }

bool MainLoop::Initialize()
{
    // initialize
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // create window
    mWindow = SDL_CreateWindow("Animation", 1024, 768, 0);
    if (!mWindow) {
        SDL_Log("failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_SetWindowResizable(mWindow, false);

    // create renderer
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if (!mRenderer) {
        SDL_Log("failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return 1;
    }

    mTicksCount = SDL_GetTicks();

    return true;
}

void MainLoop::RunLoop()
{
#ifdef __EMSCRIPTEN__
    auto callback = [](void* arg) {
        MainLoop* pApp = reinterpret_cast<MainLoop*>(arg);
        if (!pApp->IsRunning()) {
            emscripten_cancel_main_loop();
            pApp->Shutdown();
            return;
        }
        pApp->Loop();
    };
    emscripten_set_main_loop_arg(callback, this, 0, true);
#else
    while (IsRunning()) {
        Loop();
    }
    Shutdown();
#endif
}

void MainLoop::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

bool MainLoop::IsRunning()
{
    return mIsRunning;
}

void MainLoop::Loop()
{
    ProcessInput();
    Update();
    Render();
}

void MainLoop::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                mIsRunning = false;
                break;

            default:
                break;
        }
    }

    auto state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}

void MainLoop::Update()
{
#ifndef __EMSCRIPTEN__
    // Wait until 16ms has elapsed since last frame
    while (SDL_GetTicks() < mTicksCount + 16)
        ;
#endif

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    deltaTime = std::min(deltaTime, 0.05f);
    mTicksCount = SDL_GetTicks();
}

void MainLoop::Render()
{
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderPresent(mRenderer);
}
