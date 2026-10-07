#include "Application.h"

#include <algorithm>
#include <vector>

bool Application::Initialize()
{
    // initialize
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!TTF_Init()) {
        SDL_Log("failed to initialize TTF: %s", SDL_GetError());
        return false;
    }

    // create window
    mWindow = SDL_CreateWindow("Animation", 1024, 768, 0);
    if (!mWindow) {
        SDL_Log("failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    SDL_SetWindowResizable(mWindow, false);

    // create renderer
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if (!mRenderer) {
        SDL_Log("failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }

    mTicksCount = SDL_GetTicks();

    mEngine = TTF_CreateRendererTextEngine(mRenderer);
    mFont = TTF_OpenFont("resources/Roboto-Bold.ttf", 50.0f);
    mText = TTF_CreateText(mEngine, mFont, "A", 1);

    return true;
}

void Application::Loop()
{
    ProcessInput();
    Update();
    Render();
}

void Application::Shutdown()
{
    TTF_DestroyText(mText);
    TTF_CloseFont(mFont);
    TTF_DestroyRendererTextEngine(mEngine);

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    TTF_Quit();
    SDL_Quit();
}

bool Application::IsRunning()
{
    return mIsRunning;
}

void Application::ProcessInput()
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

void Application::Update()
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

void Application::Render()
{
    SDL_RenderClear(mRenderer);

    mBoardRenderer.Render(mWindow, mRenderer, mText);

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(mRenderer);
}
