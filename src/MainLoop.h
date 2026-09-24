#pragma once

#include <SDL3/SDL.h>
#include "shogi/Board.h"

class MainLoop {
public:
    MainLoop();

    bool Initialize();
    void RunLoop();
    void Shutdown();

private:
    void Loop();

    void ProcessInput();
    void Update();
    void Render();

    bool IsRunning();

    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;

    Uint32 mTicksCount = 0;
    bool mIsRunning = true;

    Board board;
};
