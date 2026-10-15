#include "Application.h"

#include <algorithm>
#include <vector>

#include "FileManager.h"
#include "reader/KifuReader.h"

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
    mFont = TTF_OpenFont("resources/font/NotoSans/NotoSansJP-Light.ttf", 50.0f);

    mBoardRenderer.Initialize(mRenderer, mFont);

    // FIXME
    std::shared_ptr<Kifu> kifu = KifuReader::Read("resources/kifu/test.kif");
    mShogi.SetKifu(kifu);

    mUserInterface.Initilaize(mWindow, mRenderer);
    mUserInterface.mFirstCallback = [&]() { mShogi.First(); };
    mUserInterface.mBackwardCallback = [&]() { mShogi.Backward(); };
    mUserInterface.mForwardCallback = [&]() { mShogi.Forward(); };
    mUserInterface.mLastCallback = [&]() { mShogi.Last(); };

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
    TTF_CloseFont(mFont);
    TTF_DestroyRendererTextEngine(mEngine);

    mUserInterface.Cleanup();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    TTF_Quit();
    SDL_Quit();
}

bool Application::IsRunning()
{
    return mIsRunning;
}

void Application::ProcessUploadedFile(std::string fileName)
{
    std::string content = FileManager::ProcessUploadedFile(fileName);

    // TODO
}

void Application::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        mUserInterface.ProcessEvent(event);
        switch (event.type) {
            case SDL_EVENT_QUIT:
                mIsRunning = false;
                break;

            case SDL_EVENT_KEY_DOWN:
                HandleKeyDown(event);
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

    int w, h;
    SDL_GetWindowSize(mWindow, &w, &h);
    unsigned int min = std::min(w, h);
    unsigned int size = min * 0.9;
    SDL_Texture* texture = mBoardRenderer.Render(mRenderer, mFont, mShogi, size, size);

    mUserInterface.CreateFrame(texture);
    mUserInterface.Render(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(mRenderer);
}

void Application::HandleKeyDown(const SDL_Event& event)
{
    switch (event.key.scancode) {
        case SDL_SCANCODE_LEFT:
            mShogi.First();
            break;

        case SDL_SCANCODE_RIGHT:
            mShogi.Last();
            break;

        case SDL_SCANCODE_UP:
            mShogi.Backward();
            break;

        case SDL_SCANCODE_DOWN:
            mShogi.Forward();
            break;

        default:
            break;
    }
}
