#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "BoardRenderer.h"

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

    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;

    Uint32 mTicksCount = 0;
    bool mIsRunning = true;

    TTF_Font* mFont;
    TTF_Text* mText;
    TTF_TextEngine* mEngine;

    BoardRenderer mBoardRenderer;
};
