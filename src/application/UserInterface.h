#pragma once

#include <SDL3/SDL.h>
#include <functional>

class UserInterface {
public:
    void Initilaize(SDL_Window* window, SDL_Renderer* renderer);

    void ProcessEvent(const SDL_Event& event);

    void CreateFrame(SDL_Texture* texture);
    void Render(SDL_Renderer* renderer);

    void Cleanup();

public:
    std::function<void(void)> mFirstCallback;
    std::function<void(void)> mBackwardCallback;
    std::function<void(void)> mForwardCallback;
    std::function<void(void)> mLastCallback;

private:
    void DisplayTexture(SDL_Texture* texture);
};
