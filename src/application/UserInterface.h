#pragma once

#include <SDL3/SDL.h>

class UserInterface {
public:
    void Initilaize(SDL_Window* window, SDL_Renderer* renderer);

    void ProcessEvent(const SDL_Event& event);

    void CreateFrame();
    void Render(SDL_Renderer* renderer);

    void Cleanup();

private:
    void DisplayTexture();
};
