#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "BoardRenderer.h"
#include "UserInterface.h"

class Application {
public:
    bool Initialize();
    void Loop();
    void Shutdown();

    bool IsRunning();

private:
    void ProcessInput();
    void Update();
    void Render();

    void HandleKeyDown(const SDL_Event& event);

    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;

    Uint32 mTicksCount = 0;
    bool mIsRunning = true;

    TTF_Font* mFont;
    TTF_TextEngine* mEngine;

    BoardRenderer mBoardRenderer;

    Shogi mShogi;

    UserInterface mUserInterface;
};
